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

	//** menu 一定要在 menuItem 添加之后再 addChild **
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

	// 如果已经下载成功，按钮不再显示“下载”而是显示“进入”
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
	// 如果当前所需文件存在，立即进入
	// 文件的默认保存地址？？？
	if(FileUtils::getInstance()->isFileExist(dlgID)){
		Scene* test = HelloWorld::createScene(dlgID);
		//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
		Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
	}

	// 如果当前所需文件不存在，发送下载请求
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

	//// 没错我就是想看到 200
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

	// 将下载的文件保存为.zip格式
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

	// 文件下载之后，提醒再次点击按钮进入场景
	download->setString("enter");
}