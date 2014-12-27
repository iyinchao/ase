#include "SearchDlg.h"
#include "ConfirmDlg.h"
#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
#include "cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CocoStudio.h"
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

	name = LabelTTF::create("Select Plane", "Arial", 50);
	name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7);
	dlgBg->addChild(name);

// ************ object select ************

	bed = ui::CheckBox::create("check_box_bed_normal.png",
                                 "check_box_bed_normal.png",
                                 "check_box_active.png",
                                 "check_box_bed_normal.png",
                                 "check_box_bed_normal.png");
	//button->setTitleText("Text Button");
	bed->setPosition(Vec2(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 3 * 2 + 10));
	bed->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setBedState, this));
	dlgBg->addChild(bed, 1);

	carbinet = ui::CheckBox::create("check_box_carbinet_normal.png",
                                 "check_box_carbinet_normal.png",
                                 "check_box_active.png",
                                 "check_box_carbinet_normal.png",
                                 "check_box_carbinet_normal.png");
	//button->setTitleText("Text Button");
	carbinet->setPosition(Vec2(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 3 * 2 + 10));
	carbinet->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setCarbinetState, this));
	dlgBg->addChild(carbinet, 1);

	light = ui::CheckBox::create("check_box_light_normal.png",
                                 "check_box_light_normal.png",
                                 "check_box_active.png",
                                 "check_box_light_normal.png",
                                 "check_box_light_normal.png");
	//button->setTitleText("Text Button");
	light->setPosition(Vec2(origin.x + dlgSize.width / 4 * 3, origin.y + dlgSize.height / 3 * 2 + 10));
	light->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setLightState, this));
	dlgBg->addChild(light, 1);

	land = ui::CheckBox::create("check_box_land_normal.png",
                                 "check_box_land_normal.png",
                                 "check_box_active.png",
                                 "check_box_land_normal.png",
                                 "check_box_land_normal.png");
	//button->setTitleText("Text Button");
	land->setPosition(Vec2(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 3 * 2 - 60));
	land->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setLandState, this));
	dlgBg->addChild(land, 1);

	table = ui::CheckBox::create("check_box_table_normal.png",
                                 "check_box_table_normal.png",
                                 "check_box_active.png",
                                 "check_box_table_normal.png",
                                 "check_box_table_normal.png");
	//button->setTitleText("Text Button");
	table->setPosition(Vec2(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 3 * 2 - 60));
	table->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setTableState, this));
	dlgBg->addChild(table, 1);

	curtain = ui::CheckBox::create("check_box_curtain_normal.png",
                                 "check_box_curtain_normal.png",
                                 "check_box_active.png",
                                 "check_box_curtain_normal.png",
                                 "check_box_curtain_normal.png");
	//button->setTitleText("Text Button");
	curtain->setPosition(Vec2(origin.x + dlgSize.width / 4 * 3, origin.y + dlgSize.height / 3 * 2 - 60));
	curtain->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setCurtainState, this));
	dlgBg->addChild(curtain, 1);

// ************ order select ************
	orderDes = ui::CheckBox::create("order_check_box_date_des_normal.png",
                                 "order_check_box_date_des_normal.png",
                                 "order_check_box_active.png",
                                 "order_check_box_date_des_normal.png",
                                 "order_check_box_date_des_normal.png");
	//button->setTitleText("Text Button");
	orderDes->setPosition(Vec2(origin.x + dlgSize.width / 4 + 20, origin.y + dlgSize.height / 3 - 10));
	orderDes->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setDateDesState, this));
	dlgBg->addChild(orderDes, 1);
	orderDes->setSelectedState(true);

	orderAsc = ui::CheckBox::create("order_check_box_date_asc_normal.png",
                                 "order_check_box_date_asc_normal.png",
                                 "order_check_box_active.png",
                                 "order_check_box_date_asc_normal.png",
                                 "order_check_box_date_asc_normal.png");
	//button->setTitleText("Text Button");
	orderAsc->setPosition(Vec2(origin.x + dlgSize.width / 4 * 3 - 20, origin.y + dlgSize.height / 3 - 10));
	orderAsc->addTouchEventListener(CC_CALLBACK_0(SearchDlg::setDateAscState, this));
	dlgBg->addChild(orderAsc, 1);
	
// ************ function button ************
	string _download("select");
	select->setFontName("Arial");
	select = MenuItemFont::create(_download, CC_CALLBACK_1(SearchDlg::menuSelectCallback, this));
	select->setPosition(origin.x + dlgSize.width/4, origin.y + dlgSize.height/7);	
	dlgMenu->addChild(select, 1);

	string _cancel("cancel");
	cancel->setFontName("Arial");
	cancel = MenuItemFont::create(_cancel, CC_CALLBACK_1(SearchDlg::menuCancelCallback, this));
	cancel->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/7);
	dlgMenu->addChild(cancel, 1);

	//** menu 一定要在 menuItem 添加之后再 addChild **
	dlgBg->addChild(dlgMenu);

// ************ 触摸吞噬 ************
	auto listener = EventListenerTouchOneByOne::create();
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
	
	// 保持排序单选框的效果
	if(orderAsc->getSelectedState()){
		orderAsc->setSelectedState(false);
	}

	CCLOG("%d", orderSelected[0]);
}

void SearchDlg::setDateAscState()
{
	orderSelected[1] = orderAsc->getSelectedState();

	// 保持排序单选框的效果
	if(orderDes->getSelectedState()){
		orderDes->setSelectedState(false);
	}

	CCLOG("%d", orderSelected[1]);
}

void SearchDlg::menuCancelCallback(Ref* pSender)
{
	this->setVisible(false);
	onExit();
	//sceneMenu->setEnabled(true);
	//outMenu->setEnabled(true);
	return;
}

void SearchDlg::menuSelectCallback(Ref* pSender)
{
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
		document.AddMember("order", "DES", allocator);
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
	httpRequest->setUrl("http://www.baidu.com");
	httpRequest->setRequestType(HttpRequest::Type::GET);
	
	//httpRequest->setUrl("http://192.168.1.106/php/scene_api.php");
	//httpRequest->setRequestType(HttpRequest::Type::POST);
	//httpRequest->setRequestData(postData, strlen(postData));

	httpRequest->setTag("select");
	httpRequest->setResponseCallback(CC_CALLBACK_2(SearchDlg::onHttpRequestComplete, this));
	HttpClient::getInstance()->send(httpRequest);
	httpRequest->release();

	return;
}

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

	// test
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

	if(_array.IsArray())
	{
		CCLOG("test");
		for(int i=0; i<_array.Capacity(); i++)
		{
			//CCLOG("%d", i);
			rapidjson::Value& arraydoc = _array[i];
			if(arraydoc.HasMember("s_id"))
			{
				const char* test = arraydoc["s_id"].GetString();
				sceneID.push_back(test);
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("b_id"))
			{
				const char* test = arraydoc["b_id"].GetString();
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("name"))
			{
				const char* test = arraydoc["name"].GetString();
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("modify_date"))
			{
				const char* test = arraydoc["modify_date"].GetString();
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("designer"))
			{
				const char* test = arraydoc["designer"].GetString();
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("download_times"))
			{
				const char* test = arraydoc["download_times"].GetString();
				//cocos2d::log(test);
			}
			if(arraydoc.HasMember("views_count"))
			{
				const char* test = arraydoc["views_count"].GetString();
				//cocos2d::log(test);
			}
		}
	}

	//cocos2d::log(sceneID[0].c_str());

	vector<string> test;

	((MeijiaMain*)this->getParent())->voidBg->setVisible(false);
	((MeijiaMain*)this->getParent())->voidBg->onExit();
	//((MeijiaMain*)this->getParent())->voidBg->removeFromParent();		// 不用使用，否则 select 间歇失效
	((MeijiaMain*)this->getParent())->addScrollView(sceneID.capacity(), sceneID);

// ***** hide searchDlg *****
	this->setVisible(false);
	onExit();

	//log("%ld", strlen(save));
	//log("%ld", t);
	//log("%s", save);
	//log("%c", save[13]);

	//// 将下载的文件保存为.zip格式
	//auto path = FileUtils::getInstance()->getWritablePath();
	//path.append(tmpDlgID + ".zip");
 //   log("confirmDlg save file path = %s",path.c_str());  
 //     
	//FILE* file = fopen(path.c_str(), "wb");
	//if(file)
	//{
	//	// strlen 在遇到 ‘\0’ 之后会结束计算长度
	//	// buffer->size() 则不会有这种限制

	//	// fputs 在遇到 ‘\0’ 之后会结束输入
	//	// fwrite 则不会有这种限制，适合写入字符块
	//	fwrite(save, sizeof(char), buffer->size(), file);
	//	// fwrite(save, sizeof(char), t, file);
	//	// fputs(save, file);
	//	fclose(file);
	//}
	//delete[] save;

	//// 文件下载之后，提醒再次点击按钮进入场景
	//download->setString("enter");
	return;
}
