#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "DialogLayer.h"
#include "ConfirmDlg.h"
#include "LoginDlg.h"

USING_NS_CC;
using namespace cocos2d::network;

Scene* MeijiaMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MeijiaMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MeijiaMain::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl("http://www.baidu.com");
	request->setResponseCallback(CC_CALLBACK_2(MeijiaMain::onHttpRequestComplete, this));
	request->setTag("GET test");
	HttpClient::getInstance()->send(request);
	request->release();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto searchItem = MenuItemImage::create(
                                           "SearchNormal.png",
                                           "SearchSelected.png",
                                           CC_CALLBACK_1(MeijiaMain::menuSearchCallback, this));
    
	searchItem->setPosition(Vec2(origin.x + visibleSize.width - searchItem->getContentSize().width/2 - 20,
        origin.y + searchItem->getContentSize().height/2 + 10));

	auto userItem = MenuItemImage::create(
                                           "UserNormal.png",
                                           "UserSelected.png",
                                           CC_CALLBACK_1(MeijiaMain::menuLoginCallback, this));
    
	userItem->setPosition(Vec2(origin.x + visibleSize.width - userItem->getContentSize().width/2 - 20,
		visibleSize.height - userItem->getContentSize().height/2 - 30));

    // create menu, it's an autorelease object
    menu = Menu::create(searchItem, userItem, NULL);
    menu->setPosition(Vec2::ZERO);

    //auto label = LabelTTF::create("meijia", "Arial", 80);
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height/4*3));
	//this->addChild(label, 1);

	auto mainBg = Sprite::create("MainBg.png", Rect(0, 0, 1024, 768));
	mainBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	auto voidBg = Sprite::create("voidBg.png");
	voidBg->setPosition(mainBg->getContentSize().width/2, mainBg->getContentSize().height/2);
	addSceneItems(voidBg);

	mainBg->addChild(voidBg, 0);
	voidBg->addChild(menu, 0);

    // add the sprite as a child to this layer
    this->addChild(mainBg, 0);
    
    return true;
}

void MeijiaMain::addSceneItems(Sprite* mainScene)
{
	int index;
	for(int i=0; i<ITEMROWS; i++)
		for(int j=0; j<ITEMCOLS; j++)
		{
			index = i*ITEMCOLS + j;
			sceneItem[index] = MenuItemImage::create(
												"BorderNormal.png",
												"BorderSelected.png",
												CC_CALLBACK_1(MeijiaMain::sceneItemCallback, this, index));
												//CC_CALLBACK_1(MeijiaMain::menuCloseCallback, this));
			sceneItem[index]->setScale(2.f);
			sceneItem[index]->setPosition(Vec2( mainScene->getContentSize().width/(ITEMCOLS+1)*(j+1),
					mainScene->getContentSize().height/(ITEMROWS+1)*(i+1)));

			menu->addChild(sceneItem[index], 1);
		}

	//// Ԥ���ӿ��ڱ߿���������֡�����ͼ��
	//auto label = LabelTTF::create("meijia", "Arial", 80);
	//label->setPosition(Vec2(sceneItem[0]->getPosition().x, sceneItem[0]->getPosition().y));
	//menu->addChild(label, 0);
}

void MeijiaMain::menuSearchCallback(Ref* pSender)
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

void MeijiaMain::menuLoginCallback(Ref* pSender)
{
	LoginDlg *logintest = LoginDlg::create();
	this->addChild(logintest, 10);
	logintest->receiveSceneMenu(menu);
	menu->setEnabled(false);
}

void MeijiaMain::sceneItemCallback(cocos2d::Ref* pSender, int id)
{
	ConfirmDlg *layertest;
	std::string dlgID;
	std::string titlestr("TITLEtitleTITLEtitle");
	std::string intro("introduction\nintroduction\nintroduction\nintroduction");
	switch(id){
	case 0:
		layertest = ConfirmDlg::create();
		dlgID = "test 1";
		layertest->setID(dlgID);
		break;
	case 1:
		layertest = ConfirmDlg::create();
		dlgID = "test 2";
		layertest->setID(dlgID);
		break;
	case 2:
		layertest = ConfirmDlg::create();
		dlgID = "test 3";
		layertest->setID(dlgID);
		break;
	case 3:
		layertest = ConfirmDlg::create();
		dlgID = "test 4";
		layertest->setID(dlgID);
		break;
	case 4:
		layertest = ConfirmDlg::create();
		dlgID = "test 5";
		layertest->setID(dlgID);
		break;
	case 5:
		layertest = ConfirmDlg::create();
		dlgID = "test 6";
		layertest->setID(dlgID);
		break;
	default:
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	}

	layertest->initLabel(intro, titlestr);
	layertest->receiveSceneMenu(menu);
	this->addChild(layertest, 10);
	menu->setEnabled(false);
}

Texture2D* MeijiaMain::Base64toTex(std::string bfile)
{
	// getFileData �����ָ������ȡ��Ŀ¼�� Resource �ļ���
	ssize_t size = 0;
	unsigned char* titlech = FileUtils::getInstance()->getFileData(bfile, "r", &size);
	std::string load_str;
	load_str = std::string((const char*)titlech, size);

	int len = 0;
	unsigned char *buffer;
	len = base64Decode((unsigned char*)load_str.c_str(), (unsigned int)load_str.length(), &buffer);

	Image* img = new Image(); 
	bool ok = img->initWithImageData(buffer, len);
	Texture2D* tex = new Texture2D();
	
	return tex;
}

void MeijiaMain::onHttpRequestComplete(HttpClient *sender, HttpResponse* response)
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
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    // _labelStatusCode->setString(statusString);
    log("response code: %d", statusCode);    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    log("Http Test, dump data: ");
	log("%s", buffer);

	char* save = new char[buffer->size()];
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        save[i] =  (*buffer)[i];
    }
	log("%s", save);
}