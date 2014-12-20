#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "DialogLayer.h"
#include "ConfirmDlg.h"
#include "LoginDlg.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
#include "MScrollView.h"

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

	//// *** 客户端与服务器链接初始化 ***
	//// 生成传输给服务器端的.json 文件
	//rapidjson::Document writedoc;
	//writedoc.SetObject();
	//rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	//rapidjson::Value array(rapidjson::kArrayType);
	//rapidjson::Value object(rapidjson::kObjectType);
	//
	//// json object 格式添加 “名称/值” 对
	//object.AddMember("inttag", 1, allocator);
	//object.AddMember("doubletag", 1.0, allocator);
	//object.AddMember("booltag", true, allocator);
	//object.AddMember("hellotag", "helloworld", allocator);
	//
	//// json 加入数组
	//array.PushBack(object, allocator);
	//
	//// json object 格式添加 “名称/值” 对
	//writedoc.AddMember("json", "json string", allocator);
	//writedoc.AddMember("array", array, allocator);

	//// 将 .json 文件转为字符流传送给服务器
	//const char* postData = writedoc.GetString();
	//request = new HttpRequest();
	//request->setRequestType(HttpRequest::Type::POST);
	//request->setUrl("http://www.baidu.com");
	//request->setResponseCallback(CC_CALLBACK_2(MeijiaMain::onHttpRequestComplete, this));
	//request->setRequestData(postData, strlen(postData));
	//request->setTag("POST test");
	//HttpClient::getInstance()->send(request);
	//request->release();
    
	// *** 客户端本地初始化 ***
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

 //   // add a "close" icon to exit the progress. it's an autorelease object
 //   auto searchItem = MenuItemImage::create(
 //                                          "SearchNormal.png",
 //                                          "SearchSelected.png",
 //                                          CC_CALLBACK_1(MeijiaMain::menuSearchCallback, this));
 //   
	//searchItem->setPosition(Vec2(origin.x + visibleSize.width - searchItem->getContentSize().width/2 - 20,
 //       origin.y + searchItem->getContentSize().height/2 + 10));

	//userItem = MenuItemImage::create(
 //                                   "UserNormal.png",
 //                                   "UserSelected.png",
 //                                   CC_CALLBACK_1(MeijiaMain::menuLoginCallback, this));

	//userItem->setPosition(Vec2(origin.x + visibleSize.width - userItem->getContentSize().width/2 - 20,
	//	visibleSize.height - userItem->getContentSize().height/2 - 30));

 //   // create menu, it's an autorelease object
 //   menu = Menu::create(searchItem, userItem, NULL);
 //   menu->setPosition(Vec2::ZERO);

	auto mainBg = Sprite::create("MainBg.png", Rect(0, 0, 1024, 768));
	mainBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//auto voidBg = Layer::create();
	//voidBg->setPosition(mainBg->getContentSize().width/2, mainBg->getContentSize().height/2);
	voidBg = MScrollView::create();
	voidBg->setPosition(0, 0);
	//voidBg->setOutMenu(menu);

	//addSceneBorder(voidBg);
	//addScenePic(voidBg);

	mainBg->addChild(voidBg, 0);
	//voidBg->addChild(menu, 1);

    // add the sprite as a child to this layer

    this->addChild(mainBg, 0);

	userVerify = false;

    return true;
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
	//if(userVerify){

	//}
	//else{
	//	logintest = LoginDlg::create();
	//	this->addChild(logintest, 10);
	//	logintest->setOutMenu(menu);
	//	logintest->setSceneMenu(voidBg->menu);
	//	voidBg->menu->setEnabled(false);
	//	menu->setEnabled(false);

	//	schedule(schedule_selector(MeijiaMain::updateCustom), 1.0f, kRepeatForever, 0);
	//	//userVerify = true;
	//}
	//return;
}

void MeijiaMain::sceneBorderCallback(cocos2d::Ref* pSender, int id)
{
	ConfirmDlg *layertest = ConfirmDlg::create();
	std::string _dlgID;
	std::string titlestr("TITLE");
	std::string intro("intro\nintro\nintro\nintro\n");
	switch(id){
	case 0:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 1:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 2:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 3:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 4:
		layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 5:
		layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	default:
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	}

	// CCLOG(_dlgID);
	layertest->initLabel(intro, titlestr);
	layertest->setSceneMenu(menu);
	this->addChild(layertest, 10);
	menu->setEnabled(false);
	return;
}

Texture2D* MeijiaMain::Base64toTex(std::string bfile)
{
	// getFileData 如果不指定，读取根目录是 Resource 文件夹
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
    //int statusCode = response->getResponseCode();
    //log("response code: %d", statusCode);
    char statusString[64] = {};
    sprintf(statusString, "HTTP tag = %s", response->getHttpRequest()->getTag());
  
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
	unsigned char* save = new unsigned char[buffer->size()];
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        save[i] =  (*buffer)[i];
    }
	log("%s", save);

	// 如果是 base64 码，则需转码
	if (response->getHttpRequest()->getTag() == "base64")
	{
		unsigned char *buffer;  
		int len = base64Decode((unsigned char*)save, strlen((char*)save), &buffer);  
	}

	// 将下载的文件保存为.zip格式
	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("baidu.html");
    log("MeijiaMainScene save file path = %s",path.c_str());  
      
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs((char*)save, file);
		fclose(file);
	}
	delete[] save;
	return;
}

void MeijiaMain::updateCustom(float dt)
{
	if(logintest->userVerify){
		log("%d", logintest->userVerify);

		Node *normalSprite = Sprite::create("VerifiedUserNormal.png");
		Node *selectedSprite = Sprite::create("VerifiedUserSelected.png");
		userItem->setNormalImage(normalSprite);
		userItem->setSelectedImage(selectedSprite);

		userVerify = true;
		this->unschedule(schedule_selector(MeijiaMain::updateCustom));
	}
}