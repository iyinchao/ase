#include "SearchDlg.h"
#include "ConfirmDlg.h"
#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include <string>
#include <stdio.h>
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;
using namespace cocos2d;
using namespace std;

bool SearchDlg::init()
{
	DialogLayer::init();
	dlgSize	= dlgBg->getContentSize();
	bgSize	= Director::getInstance()->getVisibleSize();
	origin	= Director::getInstance()->getVisibleOrigin(); 
	for(int i=0; i<6; i++) objectSelected[i] = false;
	for(int i=0; i<2; i++) orderSelected[i] = false;

	//dlgID = "test 0";

	//border = Sprite::create("BorderNormal.png");
	////border->setScale(2.f);
	//border->setPosition(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 2);
	//dlgBg->addChild(border, 1);

	name = LabelTTF::create("搜索", "华文仿宋", 50);
	name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7);
	dlgBg->addChild(name);

// ************ object select ************

	bed = ui::CheckBox::create("check_box_bed_normal.png",
                                 "check_box_bed_normal.png",
                                 "check_box_active.png",
                                 "check_box_bed_normal.png",
                                 "check_box_bed_normal.png");
	//button->setTitleText("Text Button");
    bed->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 3 * 2 + 10));
	bed->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setBedState, this));
	dlgBg->addChild(bed, 1);

	carbinet = ui::CheckBox::create("check_box_carbinet_normal.png",
                                 "check_box_carbinet_normal.png",
                                 "check_box_active.png",
                                 "check_box_carbinet_normal.png",
                                 "check_box_carbinet_normal.png");
	//button->setTitleText("Text Button");
	carbinet->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 3 * 2 + 10));
	carbinet->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setCarbinetState, this));
	dlgBg->addChild(carbinet, 1);

	light = ui::CheckBox::create("check_box_light_normal.png",
                                 "check_box_light_normal.png",
                                 "check_box_active.png",
                                 "check_box_light_normal.png",
                                 "check_box_light_normal.png");
	//button->setTitleText("Text Button");
	light->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4 * 3, origin.y + dlgSize.height / 3 * 2 + 10));
	light->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setLightState, this));
	dlgBg->addChild(light, 1);

	land = ui::CheckBox::create("check_box_land_normal.png",
                                 "check_box_land_normal.png",
                                 "check_box_active.png",
                                 "check_box_land_normal.png",
                                 "check_box_land_normal.png");
	//button->setTitleText("Text Button");
	land->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 3 * 2 - 60));
	land->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setLandState, this));
	dlgBg->addChild(land, 1);

	table = ui::CheckBox::create("check_box_table_normal.png",
                                 "check_box_table_normal.png",
                                 "check_box_active.png",
                                 "check_box_table_normal.png",
                                 "check_box_table_normal.png");
	//button->setTitleText("Text Button");
	table->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 3 * 2 - 60));
	table->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setTableState, this));
	dlgBg->addChild(table, 1);

	curtain = ui::CheckBox::create("check_box_curtain_normal.png",
                                 "check_box_curtain_normal.png",
                                 "check_box_active.png",
                                 "check_box_curtain_normal.png",
                                 "check_box_curtain_normal.png");
	//button->setTitleText("Text Button");
	curtain->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4 * 3, origin.y + dlgSize.height / 3 * 2 - 60));
	curtain->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setCurtainState, this));
	dlgBg->addChild(curtain, 1);

// ************ order select ************
	orderDes = ui::CheckBox::create("order_check_box_date_des_normal.png",
                                 "order_check_box_date_des_normal.png",
                                 "order_check_box_active.png",
                                 "order_check_box_date_des_normal.png",
                                 "order_check_box_date_des_normal.png");
	//button->setTitleText("Text Button");
	orderDes->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4 + 20, origin.y + dlgSize.height / 3 - 10));
	orderDes->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setDateDesState, this));
	dlgBg->addChild(orderDes, 1);
	orderDes->setSelectedState(true);

	orderAsc = ui::CheckBox::create("order_check_box_date_asc_normal.png",
                                 "order_check_box_date_asc_normal.png",
                                 "order_check_box_active.png",
                                 "order_check_box_date_asc_normal.png",
                                 "order_check_box_date_asc_normal.png");
	//button->setTitleText("Text Button");
	orderAsc->setPosition(cocos2d::Vec2(origin.x + dlgSize.width / 4 * 3 - 20, origin.y + dlgSize.height / 3 - 10));
	orderAsc->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setDateAscState, this));
	dlgBg->addChild(orderAsc, 1);
	
// ************ function button ************
	string _download("确认");
	select->setFontName("华文仿宋");
	select = MenuItemFont::create(_download, CC_CALLBACK_1(SearchDlg::menuSelectCallback, this));
	select->setPosition(origin.x + dlgSize.width/4, origin.y + dlgSize.height/7);	
	dlgMenu->addChild(select, 1);

	string _cancel("取消");
	cancel->setFontName("华文仿宋");
	cancel = MenuItemFont::create(_cancel, CC_CALLBACK_1(SearchDlg::menuCancelCallback, this));
	cancel->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/7);
	dlgMenu->addChild(cancel, 1);

	//** menu “ª∂®“™‘⁄ menuItem ÃÌº”÷Æ∫Û‘Ÿ addChild **
	dlgBg->addChild(dlgMenu);

// ************ ¥•√˛ÕÃ … ************
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void SearchDlg::setBedState()
{
	objectSelected[0] = bed->getSelectedState();
	CCLOG("%d", objectSelected[0]);
}

void SearchDlg::setCarbinetState()
{
	objectSelected[1] = carbinet->getSelectedState();
	CCLOG("%d", objectSelected[1]);
}

void SearchDlg::setLightState()
{
	objectSelected[2] = light->getSelectedState();
	CCLOG("%d", objectSelected[2]);
}

void SearchDlg::setLandState()
{
	objectSelected[3] = land->getSelectedState();
	CCLOG("%d", objectSelected[3]);
}

void SearchDlg::setTableState()
{
	objectSelected[4] = table->getSelectedState();
	CCLOG("%d", objectSelected[4]);
}

void SearchDlg::setCurtainState()
{
	objectSelected[5] = curtain->getSelectedState();
	CCLOG("%d", objectSelected[5]);
}

void SearchDlg::setDateDesState()
{
	orderSelected[0] = orderDes->getSelectedState();
	
	// ±£≥÷≈≈–Úµ•—°øÚµƒ–ßπ˚
	if(orderAsc->getSelectedState()){
		orderAsc->setSelectedState(false);
	}

	CCLOG("%d", orderSelected[0]);
}

void SearchDlg::setDateAscState()
{
	orderSelected[1] = orderAsc->getSelectedState();

	// ±£≥÷≈≈–Úµ•—°øÚµƒ–ßπ˚
	if(orderDes->getSelectedState()){
		orderDes->setSelectedState(false);
	}

	CCLOG("%d", orderSelected[1]);
}

void SearchDlg::menuCancelCallback(Ref* pSender)
{
	//this->setVisible(false);
	//onExit();
    this->removeFromParentAndCleanup(true);
	//sceneMenu->setEnabled(true);
	//outMenu->setEnabled(true);
	return;
}

void SearchDlg::menuSelectCallback(Ref* pSender)
{
    select->setString("搜索中……");
    
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	rapidjson::Value tagArr(rapidjson::kArrayType);

	if(bed->getSelectedState())			tagArr.PushBack(1, allocator);
	if(carbinet->getSelectedState())	tagArr.PushBack(2, allocator);
	if(light->getSelectedState())		tagArr.PushBack(3, allocator);
	if(land->getSelectedState())		tagArr.PushBack(4, allocator);
	if(table->getSelectedState())		tagArr.PushBack(5, allocator);
	if(curtain->getSelectedState())		tagArr.PushBack(6, allocator);
 
	document.AddMember("tag", tagArr, allocator);
	document.AddMember("page_now", 0, allocator);
	document.AddMember("scene_per_page", -1, allocator);

	//if(orderDated->getSelectedState())
	document.AddMember("sort_by", "modify_date", allocator);
	//else if(orderNamed->getSelectedState())
	//	document.AddMember("sort_by", "name", allocator);
	//else
	//	document.AddMember("sort_by", "", allocator);

	if(orderDes->getSelectedState())
		document.AddMember("order", "DESC", allocator);
	else if(orderAsc->getSelectedState())
		document.AddMember("order", "ASC", allocator);
 
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	//CCLog(buffer.GetString());  

	char jsonData[200]; 
	strcpy(jsonData, buffer.GetString());
	char postData[250];
	sprintf(postData, "op=client_browse&data=%s", jsonData); 
	//const char* postData = "op=client_download&data={\"s_id\": \"1234\"}";
	CCLog(postData);  

	httpRequest = new HttpRequest();
//	httpRequest->setUrl("http://www.baidu.com");
//	httpRequest->setRequestType(HttpRequest::Type::GET);
	
	httpRequest->setUrl("http://192.168.173.1:8080/php/scene_api.php");
	httpRequest->setRequestType(HttpRequest::Type::POST);
	httpRequest->setRequestData(postData, strlen(postData));

	httpRequest->setTag("select");
	httpRequest->setResponseCallback(CC_CALLBACK_2(SearchDlg::onHttpRequestComplete, this));
    HttpClient::getInstance()->setTimeoutForConnect(15);
    HttpClient::getInstance()->send(httpRequest);
	httpRequest->release();

	return;
}

void SearchDlg::connectFailed(float dt)
{
    failedLayer->setVisible(false);
    failedLayer->onExit();
}

//void SearchDlg::onExit(){
////    Layer::onExit();
//    if(listener)
//    {
//        CCLog("enter\n");
//        _eventDispatcher->removeEventListener(listener);
//    }
//}

void SearchDlg::onHttpRequestComplete(HttpClient *sender, HttpResponse* response)
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
//        select->setString("超时重新筛选");
        auto winSize = Director::getInstance()->getWinSize();
        failedLayer = DialogLayer::create();
        failedTip = LabelTTF::create("连接超时，请重新搜索", "华文仿宋", 36);
        // ************ ¥•√˛ÕÃ … ************
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event)
        {
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, failedTip);
        
        failedTip->setPosition(winSize.width/2, winSize.height/2);
        failedLayer->addChild(failedTip);
        this->addChild(failedLayer, 10);
        scheduleOnce(schedule_selector(SearchDlg::connectFailed), 1.f);
        select->setString("确认");
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
    
    // CCLog("sceneData: %s\n\nyoyoqiekenao", sceneData);
        ssize_t bufferSize = buffer->size();
        std::string load = std::string((const char*)sceneData, bufferSize);
    
    // local file test
//    ssize_t bufferSize;
//    unsigned char* jsondata = FileUtils::getInstance()->getFileData("test.json", "r", &bufferSize);
//    std::string load = std::string((const char*)jsondata, bufferSize);
    
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
        sceneID.clear();
		CCLOG("test");
		for(int i=0; i<_array.Capacity(); i++)
		{
			//CCLOG("%d", i);
			rapidjson::Value& arraydoc = _array[i];
			if(arraydoc.HasMember("s_id"))
			{
				const char* test = arraydoc["s_id"].GetString();
                CCLog("post s_id: %s", test);
				sceneID.push_back(test);
			}
		}
	}

    _eventDispatcher->removeEventListener(listener);
	((MeijiaMain*)this->getParent())->voidBg->setVisible(false);
    ((MeijiaMain*)this->getParent())->removeChild(((MeijiaMain*)this->getParent())->voidBg);
	((MeijiaMain*)this->getParent())->addScrollView(sceneID.capacity(), sceneID);

// ***** hide searchDlg *****
	this->setVisible(false);
	onExit();

	return;
}
