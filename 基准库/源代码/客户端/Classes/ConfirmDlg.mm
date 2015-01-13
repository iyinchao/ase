#include "ConfirmDlg.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "external/unzip/unzip.h"

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
    
    opened = false;

	border = Sprite::create("BorderNormal.png");
	border->setScale(0.9f);
	border->setPosition(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 2);
	dlgBg->addChild(border, 1);
	
	string _download("下载");
	download->setFontName("华文仿宋");
	download = MenuItemFont::create(_download, CC_CALLBACK_1(ConfirmDlg::menuEnterCallback, this));
	download->setPosition(origin.x + dlgSize.width/4, origin.y + dlgSize.height/7);
    download->setScale(1.2);
	dlgMenu->addChild(download, 1);

	string _cancel("取消");
	cancel->setFontName("华文仿宋");
	cancel = MenuItemFont::create(_cancel, CC_CALLBACK_1(ConfirmDlg::menuCancelCallback, this));
	cancel->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/7);
	cancel->setScale(1.2);
    dlgMenu->addChild(cancel, 1);

	//** menu “ª∂®“™‘⁄ menuItem ÃÌº”÷Æ∫Û‘Ÿ addChild **
	dlgBg->addChild(dlgMenu);
    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

void ConfirmDlg::initLabel(std::string _intro, std::string _name)
{
	intro = Label::create(_intro, "华文仿宋", 25);

	intro->setLineBreakWithoutSpace(true);
	intro->setWidth(250);
	intro->setHeight(200);
    intro->setLineBreakWithoutSpace(true);
	//intro->setMaxLineWidth(50);
	intro->setPosition(origin.x + dlgSize.width / 4*3 - 30, origin.y + dlgSize.height / 2);
	dlgBg->addChild(intro);

	name = LabelTTF::create(_name, "华文仿宋", 40);
	name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7 - 10);

	// »Áπ˚“—æ≠œ¬‘ÿ≥…π¶£¨∞¥≈•≤ª‘Ÿœ‘ æ°∞œ¬‘ÿ°±∂¯ «œ‘ æ°∞Ω¯»Î°±
    auto path = FileUtils::getInstance()->getWritablePath()+"scenes/";
    path.append(dlgID + ".zip");
	if(FileUtils::getInstance()->isFileExist(path))
		download->setString("打开");
	dlgBg->addChild(name);
	return;
}

void ConfirmDlg::setID(std::string _dlgID)
{
	dlgID = _dlgID;
    std::string thumb = "thumbs/"+_dlgID+".png";
	pic = Sprite::create(thumb);
    float sx = 0.9*256/pic->getContentSize().width;
    float sy = 0.9*256/pic->getContentSize().height;
    pic->setScale(sx, sy);
	pic->setPosition(origin.x + dlgSize.width / 4, origin.y + dlgSize.height / 2);
	dlgBg->addChild(pic, 0);

	return;
}

void ConfirmDlg::disappear(){
  //  sceneMenu->setEnabled(true);
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
    onExit();
	//sceneMenu->setEnabled(true);
	return;
}

void ConfirmDlg::onExit(){
    Layer::onExit();
    if(listener)
    {
//        CCLog("enter\n");
        _eventDispatcher->removeEventListener(listener);
    }
}

void ConfirmDlg::menuEnterCallback(Ref* pSender)
{
	// »Áπ˚µ±«∞À˘–ËŒƒº˛¥Ê‘⁄£¨¡¢º¥Ω¯»Î
	// Œƒº˛µƒƒ¨»œ±£¥Êµÿ÷∑£ø£ø£ø
	std::string tmpDlgID = dlgID;
    
    if(opened)
        return;
  //  opened = true;

    //for test
 //   Scene* test = HelloWorld::createScene(tmpDlgID);
    //Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
 //   Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
 //   return;
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath()+"scenes/"+tmpDlgID+".zip";
    
	if(FileUtils::getInstance()->isFileExist(fullpath)){
        opened = true;
		Scene* test = HelloWorld::createScene(tmpDlgID, name->getString(), intro->getString());
		//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
		Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
	}

	// »Áπ˚µ±«∞À˘–ËŒƒº˛≤ª¥Ê‘⁄£¨∑¢ÀÕœ¬‘ÿ«Î«Û
	else{
		download->setString("下载中……");

		//// *** øÕªß∂À”Î∑˛ŒÒ∆˜¡¥Ω”≥ı ºªØ ***
		//// …˙≥…¥´ ‰∏¯∑˛ŒÒ∆˜∂Àµƒ.json Œƒº˛
		//rapidjson::Document writedoc;
		//writedoc.SetObject();
		//rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	
		//// json object ∏Ò ΩÃÌº” °∞√˚≥∆/÷µ°± ∂‘
		//writedoc.AddMember("s_id", dlgID.c_str(), allocator);
		//const char* tmpData = writedoc.GetString();

		char postData[80];
		sprintf(postData, "op=client_download&data={\"s_id\":\"%s\"}", tmpDlgID.c_str()); 
		//const char* postData = "op=client_download&data={\"s_id\": \"1234\"}";

		requestDlg = new HttpRequest();
	//	requestDlg->setUrl("http://www.baidu.com");
	//	requestDlg->setRequestType(HttpRequest::Type::GET);

		requestDlg->setRequestType(HttpRequest::Type::POST);
		requestDlg->setUrl("http://192.168.173.1:8080/php/scene_api.php");
		requestDlg->setRequestData(postData, strlen(postData));

		requestDlg->setResponseCallback(CC_CALLBACK_2(ConfirmDlg::onHttpRequestComplete, this));
		requestDlg->setTag("scene");
        HttpClient::getInstance()->setTimeoutForConnect(40);
		HttpClient::getInstance()->send(requestDlg);
		requestDlg->release();
	}
	return;
}

void ConfirmDlg::connectFailed(float dt)
{
    failedLayer->setVisible(false);
    failedLayer->onExit();
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

	//// √ª¥ÌŒ“æÕ «œÎø¥µΩ 200
    int statusCode = response->getResponseCode();
	log("response code: %d", statusCode);
    if(statusCode == -1)
    {
        //        select->setString("超时重新筛选");
        auto winSize = Director::getInstance()->getWinSize();
        failedLayer = DialogLayer::create();
        failedTip = LabelTTF::create("连接超时，请重新下载", "华文仿宋", 36);
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
        scheduleOnce(schedule_selector(ConfirmDlg::connectFailed), 1.f);
        download->setString("下载");
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

	char* save = new char[buffer->size()];
	int t=0;
	for (long i = 0; i < buffer->size(); i++)
    {
		t++;
        save[i] =  (*buffer)[i];
    }
    
    // 匹配场景文件不存在
    if(!strcmp(save, "{\"status\":\"NO_SCENE\"}"))
    {
        download->setString("该场景已删除！");
        return;
    }
	//log("%ld", strlen(save));
	//log("%ld", t);
	//log("%s", save);
	//log("%c", save[13]);

	// Ω´œ¬‘ÿµƒŒƒº˛±£¥ÊŒ™.zip∏Ò Ω
	auto path = FileUtils::getInstance()->getWritablePath()+"scenes/";
	path.append(tmpDlgID + ".zip");
    log("confirmDlg save file path = %s",path.c_str());  
      
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		// strlen ‘⁄”ˆµΩ °Æ\0°Ø ÷Æ∫Ûª·Ω· ¯º∆À„≥§∂»
		// buffer->size() ‘Ú≤ªª·”–’‚÷÷œﬁ÷∆

		// fputs ‘⁄”ˆµΩ °Æ\0°Ø ÷Æ∫Ûª·Ω· ¯ ‰»Î
		// fwrite ‘Ú≤ªª·”–’‚÷÷œﬁ÷∆£¨  ∫œ–¥»Î◊÷∑˚øÈ
		fwrite(save, sizeof(char), buffer->size(), file);
		// fwrite(save, sizeof(char), t, file);
		// fputs(save, file);
		fclose(file);
        
        ZipFile z(path);
        unzFile zipFile = unzOpen(path.c_str());
        unz_file_info64 fileInfo;
        char curName[257];
        int err = unzGoToFirstFile64(zipFile, &fileInfo, curName, sizeof(curName)-1);
        std::vector<std::string> names;
        while(err == UNZ_OK){
            names.push_back(curName);
            err = unzGoToNextFile64(zipFile, &fileInfo, curName, sizeof(curName)-1);
        }

        std::string fullname = FileUtils::getInstance()->getWritablePath()+"scenes/"+tmpDlgID;

        // create dir
        NSString *fullFilePath = [NSString stringWithFormat:@"%s", fullname.c_str()];
        BOOL isDir = NO;
        NSFileManager *fileManager = [NSFileManager defaultManager];
        BOOL exsit = [fileManager fileExistsAtPath:fullFilePath isDirectory:&isDir];
        if (!isDir || !exsit) {
            [fileManager createDirectoryAtPath:fullFilePath withIntermediateDirectories:YES attributes:nil error:nil];
        }

        fullname = fullname + "/";
        for (int i=0; i<names.size(); i++) {
            std::string filePath = fullname + names[i];
            CCLOG("name:%s\n",names[i].c_str());
            if(names[i][names[i].size()-1] == '/'){
                filePath[filePath.size()-1] = 0;
                CCLOG("dirpath:%s\n",filePath.c_str());
                NSString *fullFPath = [NSString stringWithFormat:@"%s", filePath.c_str()];
                BOOL isDir1 = NO;
                NSFileManager *fileManager1 = [NSFileManager defaultManager];
                BOOL exsit1 = [fileManager1 fileExistsAtPath:fullFPath isDirectory:&isDir1];
                if (!isDir1 || !exsit1) {
                    [fileManager createDirectoryAtPath:fullFPath withIntermediateDirectories:YES attributes:nil error:nil];
                }
            }
        }
        for (int i=0; i<names.size(); i++) {
            std::string filePath = fullname + names[i];
            if(names[i][names[i].size()-1] != '/'){
                FILE *fp = fopen(filePath.c_str(), "wb");
                ssize_t s;
                unsigned char *buffer = z.getFileData(names[i], &s);
                fwrite(buffer, s, 1, fp);
                fclose(fp);
                free(buffer);
            }
        }
	}
	delete[] save;

	// Œƒº˛œ¬‘ÿ÷Æ∫Û£¨Ã·–—‘Ÿ¥Œµ„ª˜∞¥≈•Ω¯»Î≥°æ∞
	download->setString("打开");
	return;
}