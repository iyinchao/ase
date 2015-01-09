#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "DialogLayer.h"
#include "ConfirmDlg.h"
#include "LoginDlg.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
#include "MScrollView.h"
#include "SearchDlg.h"
#include <map>

USING_NS_CC;
USING_NS_CC_EXT;
//using namespace gui;
using namespace cocos2d::network;
using namespace cocos2d;
using namespace std;

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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TheRain.mp3", true);
	sceneNum = SCENESUM;
	intro.clear();
	sname.clear();

	vector<string> test;
	for(int i=1; i<sceneNum; i++)
		test.push_back("0b7587a9-940c-4965-9cbc-45c3a1380ae5");

	for(int i=0; i<sceneNum; i++)
	{
		intro.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "intro"));
		sname.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "name"));
		designer.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "designer"));
		mdate.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "date"));
	}

	// *** 客户端本地初始化 ***
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto searchItem = MenuItemImage::create(
                                           "SearchNormal.png",
                                           "SearchSelected.png",
                                           CC_CALLBACK_1(MeijiaMain::menuSearchCallback, this));
    
	searchItem->setPosition(Vec2(origin.x + visibleSize.width - searchItem->getContentSize().width/2 - 20,
        origin.y + searchItem->getContentSize().height/2 + 30));

	//userItem = MenuItemImage::create(
 //                                   "UserNormal.png",
 //                                   "UserSelected.png",
 //                                   CC_CALLBACK_1(MeijiaMain::menuLoginCallback, this));

	//userItem->setPosition(Vec2(origin.x + visibleSize.width - userItem->getContentSize().width/2 - 20,
	//	visibleSize.height - userItem->getContentSize().height/2 - 30));

	updateItem = MenuItemImage::create(
                                    "update.png",
                                    "update.png",
                                    CC_CALLBACK_1(MeijiaMain::menuUpdateCallback, this));

	updateItem->setPosition(Vec2(origin.x + visibleSize.width - updateItem->getContentSize().width/2 - 20,
		visibleSize.height - updateItem->getContentSize().height/2 - 30));

    // create menu, it's an autorelease object
    menu = Menu::create(searchItem, updateItem, NULL);
    menu->setPosition(Vec2::ZERO);

	mainBg = Sprite::create("MainBg2.png", Rect(0, 0, 1024, 768));
	mainBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//voidBg = MScrollView::create();
	//voidBg->initScrollView(9, test);
	//voidBg->setPosition(0, 0);
	this->addScrollView(test.capacity(), test);

	//mainBg->addChild(voidBg, 0);
	//voidBg->addChild(menu, 0);
	//voidBg->addChild(menu, 1);

    this->addChild(mainBg, 0);

	userVerify = false;

    return true;
}

void MeijiaMain::updateSceneInfo()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	rapidjson::Value tagArr(rapidjson::kArrayType);
	
	document.AddMember("page_now", 0, allocator);
	document.AddMember("scene_per_page", -1, allocator);
 
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	//CCLog(buffer.GetString());  

	char jsonData[200]; 
	strcpy(jsonData, buffer.GetString());
	char postData[250];
	sprintf(postData, "op=client_browse&data=%s", jsonData); 
	CCLog(postData);  

	MhttpRequest = new HttpRequest();
	MhttpRequest->setUrl("http://www.baidu.com");
	MhttpRequest->setRequestType(HttpRequest::Type::GET);
	
	//MhttpRequest->setUrl("http://192.168.1.106/php/scene_api.php");
	//MhttpRequest->setRequestType(HttpRequest::Type::POST);
	//MhttpRequest->setRequestData(postData, strlen(postData));

	MhttpRequest->setTag("select");
	MhttpRequest->setResponseCallback(CC_CALLBACK_2(MeijiaMain::onHttpRequestComplete, this));
	HttpClient::getInstance()->send(MhttpRequest);
	MhttpRequest->release();
}

void MeijiaMain::addScrollView(int _sceneNum, vector<string>& _test)
{
	voidBg = MScrollView::create();
	voidBg->initScrollView(_sceneNum, _test);
	voidBg->setPosition(0, 0);
	mainBg->addChild(voidBg, 0);
	voidBg->addChild(menu, 0);

	return;
}

void MeijiaMain::menuSearchCallback(Ref* pSender)
{
	// 停止旋转，恢复原状 test
	updateItem->stopAllActions();
	updateItem->setRotation(0);

	//auto uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("SelectPlane.json");
	//Director::getInstance()->end();

	searchtest = SearchDlg::create();
	this->addChild(searchtest, 10);
	searchtest->setOutMenu(menu);
	searchtest->setSceneMenu(voidBg->menu);
	//voidBg->menu->setEnabled(false);
	//menu->setEnabled(false);
}

//void MeijiaMain::menuLoginCallback(Ref* pSender)
//{
//	if(userVerify){
//
//	}
//	else{
//		logintest = LoginDlg::create();
//		this->addChild(logintest, 10);
//		//logintest->setOutMenu(menu);
//		//logintest->setSceneMenu(voidBg->menu);
//		//voidBg->menu->setEnabled(false);
//		//menu->setEnabled(false);
//
//		schedule(schedule_selector(MeijiaMain::updateCustom), 1.0f, kRepeatForever, 0);
//		//userVerify = true;
//	}
//	return;
//}

void MeijiaMain::menuUpdateCallback(Ref* pSender)
{
	RotateBy* rotate = RotateBy::create(1, 360);
	RepeatForever* repeatRotate = RepeatForever::create(rotate);
	//updateItem->runAction(Spawn::create(rotate, NULL));
	updateItem->runAction(repeatRotate);

	auto winSize = Director::getInstance()->getWinSize();
	updateLayer = DialogLayer::create();
	auto updating = LabelTTF::create("updating... please wait", "Arial", 36);
	// ************ 触摸吞噬 ************
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, updating);

	updating->setPosition(winSize.width/2, winSize.height/2);
	updateLayer->addChild(updating);
	this->addChild(updateLayer, 10);
	//updateSceneInfo();

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

	// 没错我就是想看到 200
    int statusCode = response->getResponseCode();
	log("response code: %d", statusCode);    
	
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

	char* sceneData = new char[buffer->size()];
	int t=0;
	for (long i = 0; i < buffer->size(); i++)
    {
        sceneData[i] =  (*buffer)[i];
    }

	// local file test
	ssize_t bufferSize;
	unsigned char* jsondata = FileUtils::getInstance()->getFileData("test.json", "r", &bufferSize);
	std::string load = std::string((const char*)jsondata, bufferSize);

	rapidjson::Document readdoc;
	readdoc.Parse<0>(load.c_str());
    if (readdoc.HasParseError())
    {
		CCLog("GetParseError:%s\n",readdoc.GetParseError());
    }

	rapidjson::Value& _json = readdoc["status"];
	const char* ch = _json.GetString();
	cocos2d::log(ch);
	cocos2d::log(_json.GetString());

	rapidjson::Value& _array = readdoc["scene"];
	const char* s_id;

	if(_array.IsArray())
	{
		CCLOG("test");
		sname.clear();
		intro.clear();
		designer.clear();
		mdate.clear();

		for(int i=0; i<_array.Capacity(); i++)
		{
			//CCLOG("%d", i);
			rapidjson::Value& arraydoc = _array[i];
			if(arraydoc.HasMember("s_id"))
			{
				s_id = arraydoc["s_id"].GetString();
			}
			if(arraydoc.HasMember("name"))
			{
				const char* tname = arraydoc["name"].GetString();
				sname.insert(pair<string, string>(s_id, tname));
			}
			if(arraydoc.HasMember("desc"))
			{
				const char* tdesc = arraydoc["desc"].GetString();
				intro.insert(pair<string, string>(s_id, tdesc));
			}
			if(arraydoc.HasMember("designer"))
			{
				const char* tdesigner = arraydoc["designer"].GetString();
				designer.insert(pair<string, string>(s_id, tdesigner));
			}
			if(arraydoc.HasMember("mod_date"))
			{
				const char* tmdate = arraydoc["mod_date"].GetString();
				mdate.insert(pair<string, string>(s_id, tmdate));
			}
		}
	}

	voidBg->setScrollInfo(sname, intro, designer, mdate);

	// 停止更新（旋转），恢复原状 test
	updateItem->stopAllActions();
	updateItem->setRotation(0);
	updateLayer->setVisible(false);
	updateLayer->onExit();

	return;
}

//void MeijiaMain::updateCustom(float dt)
//{
//	if(logintest->userVerify){
//		log("%d", logintest->userVerify);
//
//		Node *normalSprite = Sprite::create("VerifiedUserNormal.png");
//		Node *selectedSprite = Sprite::create("VerifiedUserSelected.png");
//		userItem->setNormalImage(normalSprite);
//		userItem->setSelectedImage(selectedSprite);
//
//		userVerify = true;
//		this->unschedule(schedule_selector(MeijiaMain::updateCustom));
//	}
//}