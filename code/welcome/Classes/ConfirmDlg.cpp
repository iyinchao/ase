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

void ConfirmDlg::initLabel(std::string _intro, std::string _name)
{
	intro = Label::create(_intro, "Arial", 30);

	intro->setLineBreakWithoutSpace(true);
	intro->setWidth(100);
	intro->setHeight(200);
	intro->setMaxLineWidth(50);
	intro->setPosition(origin.x + dlgSize.width / 4*3, origin.y + dlgSize.height / 2);
	dlgBg->addChild(intro);

	name = LabelTTF::create(_name, "Arial", 50);
	name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7);

	// ����Ѿ����سɹ�����ť������ʾ�����ء�������ʾ�����롱
	if(FileUtils::getInstance()->isFileExist(dlgID))
		download->setString("enter");

	dlgBg->addChild(name);
	return;
}

void ConfirmDlg::setID(std::string _dlgID)
{
	dlgID = _dlgID;
	return;
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
	return;
}

void ConfirmDlg::menuEnterCallback(Ref* pSender)
{
	// �����ǰ�����ļ����ڣ���������
	// �ļ���Ĭ�ϱ����ַ������
	std::string tmpDlgID = dlgID;

	if(FileUtils::getInstance()->isFileExist(tmpDlgID)){
		Scene* test = HelloWorld::createScene(tmpDlgID);
		//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
		Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
	}

	// �����ǰ�����ļ������ڣ�������������
	else{
		download->setString("downloading...");

		//// *** �ͻ�������������ӳ�ʼ�� ***
		//// ���ɴ�����������˵�.json �ļ�
		//rapidjson::Document writedoc;
		//writedoc.SetObject();
		//rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	
		//// json object ��ʽ��� ������/ֵ�� ��
		//writedoc.AddMember("s_id", dlgID.c_str(), allocator);
		//const char* tmpData = writedoc.GetString();

		char postData[80];
		sprintf(postData, "op=client_download&data={\"s_id\":\"%s\"}", tmpDlgID.c_str()); 
		//const char* postData = "op=client_download&data={\"s_id\": \"1234\"}";

		requestDlg = new HttpRequest();
		requestDlg->setRequestType(HttpRequest::Type::POST);
		//requestDlg->setUrl("http://192.168.1.105/php/scene_api.php");
		requestDlg->setUrl("http://www.baidu.com");
		requestDlg->setResponseCallback(CC_CALLBACK_2(ConfirmDlg::onHttpRequestComplete, this));
		requestDlg->setRequestData(postData, strlen(postData));
		requestDlg->setTag("scene");
		HttpClient::getInstance()->send(requestDlg);
		requestDlg->release();
	}
	return;
}

void ConfirmDlg::onHttpRequestComplete(HttpClient *sender, HttpResponse* response)
{
	std::string tmpDlgID = this->dlgID;
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
    log("Http Test, dump data: ");
	log("%s", response->getResponseData());

	char* save = new char[buffer->size()];
	int t=0;
	for (long i = 0; i < buffer->size(); i++)
    {
		t++;
        save[i] =  (*buffer)[i];
    }
	//log("%ld", strlen(save));
	//log("%ld", t);
	//log("%s", save);
	//log("%c", save[13]);

	// �����ص��ļ�����Ϊ.zip��ʽ
	auto path = FileUtils::getInstance()->getWritablePath();
	path.append(tmpDlgID + ".zip");
    log("confirmDlg save file path = %s",path.c_str());  
      
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		// strlen ������ ��\0�� ֮���������㳤��
		// buffer->size() �򲻻�����������

		// fputs ������ ��\0�� ֮����������
		// fwrite �򲻻����������ƣ��ʺ�д���ַ���
		fwrite(save, sizeof(char), buffer->size(), file);
		// fwrite(save, sizeof(char), t, file);
		// fputs(save, file);
		fclose(file);
	}
	delete[] save;

	// �ļ�����֮�������ٴε����ť���볡��
	download->setString("enter");
	return;
}