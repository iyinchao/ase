#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "DialogLayer.h"
#include "ConfirmDlg.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("The Rain.mp3", true);                                                                                                 
    
	sceneNum = SCENESUM;
    intro.clear();
    sname.clear();
    designer.clear();
    mdate.clear();
    
    // vector<string> test;
    sceneID.push_back("3d97adf8-fa20-4fd4-850d-bd00b57ac22a");
    sceneID.push_back("7a38b72e-63c3-459f-89c4-0633ab2540da");
    sceneID.push_back("36dc3fbc-3c2a-4e68-9bee-f4dea7deb425");
    sceneID.push_back("94a3b955-3d0d-496c-873b-8d47ea263b5d");
    sceneID.push_back("450a653f-3d3a-455f-9772-504a3237337a");
    sceneID.push_back("a90cb734-83e7-498f-bc5b-1f4e84f074f3");
    sceneID.push_back("ba1af250-05ed-426a-b210-2471af24083f");
    sceneID.push_back("e7d9c34b-f629-4798-ad3a-1c30206c85cb");
    
    for(int i=0; i<sceneID.capacity(); i++)
    {
        intro.insert(pair<string, string>(sceneID[i], "这里是场景介绍"));
        sname.insert(pair<string, string>(sceneID[i], "场景名称"));
        designer.insert(pair<string, string>(sceneID[i], "场景设计师"));
        mdate.insert(pair<string, string>(sceneID[i], "修改时间"));
    }

	// *** øÕªß∂À±æµÿ≥ı ºªØ ***
    Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto searchItem = MenuItemImage::create(
                                            "SearchNormal.png",
                                            "SearchSelected.png",
                                            CC_CALLBACK_1(MeijiaMain::menuSearchCallback, this));
    
    searchItem->setPosition(cocos2d::Vec2(origin.x + visibleSize.width - searchItem->getContentSize().width/2 - 20,
                                 origin.y + searchItem->getContentSize().height/2 + 30));
    
    updateItem = MenuItemImage::create(
                                       "update.png",
                                       "update.png",
                                       CC_CALLBACK_1(MeijiaMain::menuUpdateCallback, this));
    
    updateItem->setPosition(cocos2d::Vec2(origin.x + visibleSize.width - updateItem->getContentSize().width/2 - 20,
                                 visibleSize.height - updateItem->getContentSize().height/2 - 30));
    
    // create menu, it's an autorelease object
    menu = Menu::create(searchItem, updateItem, NULL);
    menu->setPosition(cocos2d::Vec2::ZERO);
    
    mainBg = Sprite::create("MainBg.png", Rect(0, 0, 1024, 768));
    mainBg->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addScrollView(sceneID.capacity(), sceneID);
    
    this->addChild(menu, 1);
    this->addChild(mainBg, 0);
    
    userVerify = false;
    // updateSceneInfo();
    
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
//    MhttpRequest->setUrl("http://www.baidu.com");
//    MhttpRequest->setRequestType(HttpRequest::Type::GET);
    
    MhttpRequest->setUrl("http://192.168.173.1:8080/php/scene_api.php");
    MhttpRequest->setRequestType(HttpRequest::Type::POST);
    MhttpRequest->setRequestData(postData, strlen(postData));
    
    MhttpRequest->setTag("select");
    MhttpRequest->setResponseCallback(CC_CALLBACK_2(MeijiaMain::onHttpRequestComplete, this));
    HttpClient::getInstance()->setTimeoutForConnect(15);
    HttpClient::getInstance()->send(MhttpRequest);
    MhttpRequest->release();
}

void MeijiaMain::addScrollView(int _sceneNum, vector<string>& _test)
{
	voidBg = MScrollView::create();
	voidBg->initScrollView(_sceneNum, _test);
	voidBg->setPosition(0, 0);
    voidBg->setScrollInfo(sname, intro, designer, mdate);
	mainBg->addChild(voidBg, 0);

	return;
}

void MeijiaMain::menuSearchCallback(Ref* pSender)
{
	searchtest = SearchDlg::create();
	this->addChild(searchtest, 10);
	searchtest->setOutMenu(menu);
	searchtest->setSceneMenu(voidBg->menu);
}

void MeijiaMain::menuUpdateCallback(Ref* pSender)
{
    RotateBy* rotate = RotateBy::create(1, 360);
    RepeatForever* repeatRotate = RepeatForever::create(rotate);
    //updateItem->runAction(Spawn::create(rotate, NULL));
    updateItem->runAction(repeatRotate);
    
    auto winSize = Director::getInstance()->getWinSize();
    updateLayer = DialogLayer::create();
    updating = LabelTTF::create("场景信息更新……请稍候", "华文仿宋", 36);
    // ************ ¥•√˛ÕÃ … ************
    updateLayer->dlistener = EventListenerTouchOneByOne::create();
    updateLayer->dlistener->setSwallowTouches(true);
    updateLayer->dlistener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(updateLayer->dlistener, updating);
    
    updating->setPosition(winSize.width/2, winSize.height/2);
    updateLayer->addChild(updating);
    this->addChild(updateLayer, 10);
    updateSceneInfo();
    
    return;
}

Texture2D* MeijiaMain::Base64toTex(std::string bfile)
{
	// getFileData »Áπ˚≤ª÷∏∂®£¨∂¡»°∏˘ƒø¬º « Resource Œƒº˛º–
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

void MeijiaMain::updateFinished(float dt)
{
    updateItem->stopAllActions();
    updateItem->setRotation(0);
    updateLayer->setVisible(false);
    updateLayer->onExit();
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
    
    // √ª¥ÌŒ“æÕ «œÎø¥µΩ 200
    int statusCode = response->getResponseCode();
    log("response code: %d", statusCode);
    if(statusCode == -1)
    {
        updating->setString("连接超时，场景更新失败");
        scheduleOnce(schedule_selector(MeijiaMain::updateFinished), 1.f);
    }
    
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
    
    CCLog("sceneData: %s\n\nyoyoqiekenao", sceneData);
    // local file test
    ssize_t bufferSize = buffer->size();
    std::string load = std::string((const char*)sceneData, bufferSize);
    
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
    
    if(_array.IsArray())
    {
        CCLOG("test");
        sceneID.clear();
        sname.clear();
        intro.clear();
        designer.clear();
        mdate.clear();
        const char* s_id;
        
        for(int i=0; i<_array.Capacity(); i++)
        {
            //CCLOG("%d", i);
            rapidjson::Value& arraydoc = _array[i];
            if(arraydoc.HasMember("s_id"))
            {
                s_id = arraydoc["s_id"].GetString();
                sceneID.push_back(s_id);
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
                CCLog("post intro: %s", tdesc);
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
    
    this->voidBg->setVisible(false);
    this->removeChild(this->voidBg);
    this->addScrollView(sceneID.capacity(), sceneID);
    voidBg->setScrollInfo(sname, intro, designer, mdate);
    
    // Õ£÷π∏¸–¬£®–˝◊™£©£¨ª÷∏¥‘≠◊¥ test
    updateItem->stopAllActions();
    updateItem->setRotation(0);
    updateLayer->setVisible(false);
    updateLayer->onExit();
    
    return;
}