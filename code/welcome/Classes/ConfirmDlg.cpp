#include "ConfirmDlg.h"
#include "HelloWorldScene.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace std;

bool ConfirmDlg::init()
{
	DialogLayer::init();
	dlgSize	= dlgBg->getContentSize();
	bgSize	= Director::getInstance()->getVisibleSize();
	origin	= Director::getInstance()->getVisibleOrigin(); 
	dlgID = "test 0";

	border = Sprite::create("BorderNormal.png");
	border->setScale(2.f);
	border->setPosition(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 2);
	dlgBg->addChild(border, 1);
	
	string _download("download");
	download = MenuItemFont::create(_download, CC_CALLBACK_1(ConfirmDlg::menuEnterCallback, this));
	download->setPosition(origin.x + dlgSize.width/4, origin.y + dlgSize.height/7);
	dlgMenu->addChild(download, 1);

	string _cancel("cancel");
	cancel = MenuItemFont::create(_cancel, CC_CALLBACK_1(ConfirmDlg::menuCancelCallback, this));
	cancel->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/7);
	dlgMenu->addChild(cancel, 1);

	//** menu һ��Ҫ�� menuItem ���֮���� addChild **
	dlgBg->addChild(dlgMenu);
	return true;
}

void ConfirmDlg::initLabel(std::string &_intro, std::string &_name)
{
	intro = Label::create(_intro, "", 30);
	intro->setLineBreakWithoutSpace(true);
	//intro->setWidth(100);
	//intro->setHeight(200);
	//intro->setMaxLineWidth(50);
	intro->setPosition(origin.x + dlgSize.width / 4*3, origin.y + dlgSize.height / 2);
	dlgBg->addChild(intro);

	name = LabelTTF::create(_name, "", 50);
	name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7);

	// ����Ѿ����سɹ�����ť������ʾ�����ء�������ʾ�����롱
	if(FileUtils::getInstance()->isFileExist(dlgID))
		download->setString("enter");

	dlgBg->addChild(name);
}

void ConfirmDlg::setID(std::string &_dlgID)
{
	dlgID = _dlgID;
}

void ConfirmDlg::menuCloseCallback(Ref* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ConfirmDlg::menuCancelCallback(Ref* pSender)
{
	this->setVisible(false);
	sceneMenu->setEnabled(true);
}

void ConfirmDlg::menuEnterCallback(Ref* pSender)
{
	// �����ǰ�����ļ����ڣ���������
	// �ļ���Ĭ�ϱ����ַ������
	if(FileUtils::getInstance()->isFileExist(dlgID)){
		Scene* test = HelloWorld::createScene(dlgID);
		//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
		Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
	}

	// �����ǰ�����ļ������ڣ�������������
	else{
		download->setString("downloading...");

		requestDlg = new HttpRequest();
		requestDlg->setRequestType(HttpRequest::Type::GET);
		requestDlg->setUrl("http://www.baidu.com");
		requestDlg->setResponseCallback(CC_CALLBACK_2(ConfirmDlg::onHttpRequestComplete, this));
		requestDlg->setTag("scene");
		HttpClient::getInstance()->send(requestDlg);
		requestDlg->release();
	}
}

void ConfirmDlg::onHttpRequestComplete(HttpClient *sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }    
 
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    } 

	//// û���Ҿ����뿴�� 200
    //int statusCode = response->getResponseCode();
	//log("response code: %d", statusCode);    
	
    char statusString[64] = {};
    log(statusString, "HTTP Status, tag = %s", response->getHttpRequest()->getTag());

    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }

    // dump data
    std::vector<char> *buffer = response->getResponseData();
    //log("Http Test, dump data: ");
	//log("%s", buffer);

	char* save = new char[buffer->size()];
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        save[i] =  (*buffer)[i];
    }
	log("%s", save);

	// �����ص��ļ�����Ϊ.zip��ʽ
	auto path = FileUtils::getInstance()->getWritablePath();
	path.append(dlgID);
	path.append(".zip");
    log("confirmDlg save file path = %s",path.c_str());  
      
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs(save, file);
		fclose(file);
	}
	delete[] save;

	// �ļ�����֮�������ٴε����ť���볡��
	download->setString("enter");
}