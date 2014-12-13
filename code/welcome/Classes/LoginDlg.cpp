#include "LoginDlg.h"
#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace cocos2d::network;

bool LoginDlg::init()
{
	DialogLayer::init();
	dlgSize	= dlgBg->getContentSize();
	bgSize	= Director::getInstance()->getVisibleSize();
	origin	= Director::getInstance()->getVisibleOrigin(); 
	dlgID = "test 0";

	Sprite *emailLogo = Sprite::create("email.png");
	emailLogo->setPosition(dlgSize.width/6, dlgSize.height/4*3);
	dlgBg->addChild(emailLogo);

	Sprite *passwordLogo = Sprite::create("password.png");
	passwordLogo->setPosition(dlgSize.width/6, dlgSize.height/2);
	dlgBg->addChild(passwordLogo);

	auto emailBoxSize = Size(dlgSize.width - 200, 60);
	emailBox = EditBox::create(emailBoxSize, Scale9Sprite::create("input.png"));
	emailBox->setFontSize(10);
	emailBox->setPlaceholderFontSize(10);
	emailBox->setPosition(Vec2(emailLogo->getContentSize().width + dlgSize.width /2, emailLogo->getPosition().y));
    
    emailBox->setFontColor(Color3B::RED);
	
    //emailBox->setPlaceHolder("E-mail..");
	emailBox->setPlaceholderFontColor(Color3B::GRAY);
    //emailBox->setMaxLength(8);
	emailBox->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
    emailBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    emailBox->setDelegate(this);
    dlgBg->addChild(emailBox);

	auto passwordBoxSize = Size(dlgSize.width - 200, 60);
	passwordBox = EditBox::create(emailBoxSize, Scale9Sprite::create("input.png"));
	passwordBox->setPosition(Vec2(passwordLogo->getContentSize().width + dlgSize.width /2, passwordLogo->getPosition().y));
    passwordBox->setFontSize(20);
    passwordBox->setFontColor(Color3B::RED);
	passwordBox->setPlaceholderFontSize(20);
    passwordBox->setPlaceHolder("password..");
	passwordBox->setPlaceholderFontColor(Color3B::GRAY);
    // email->setMaxLength(8);
	passwordBox->setInputFlag(EditBox::InputFlag::PASSWORD);
    passwordBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    passwordBox->setDelegate(this);
    dlgBg->addChild(passwordBox);

	//emailBg = Sprite::create("input.png");
	//emailBg->setPosition(Vec2(emailLogo->getContentSize().width + dlgSize.width /2, dlgSize.height/4*3));
	//dlgBg->addChild(emailBg, 0);
	//tf = TextFieldTTF::textFieldWithPlaceHolder("input here", "宋体", 20);
	//tf->setColorSpaceHolder(Color3B::BLUE);
 //   tf->setPosition(Vec2(emailLogo->getContentSize().width + dlgSize.width /2, dlgSize.height/4*3));
 //   dlgBg->addChild(tf, 1);

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(LoginDlg::onTouchBegan, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	string _login("login");
	login = MenuItemFont::create(_login, CC_CALLBACK_1(LoginDlg::menuLoginCallback, this));
	login->setPosition(origin.x + dlgSize.width/4, origin.y + dlgSize.height/7);
	dlgMenu->addChild(login, 1);

	string _cancel("cancel");
	cancel = MenuItemFont::create(_cancel, CC_CALLBACK_1(LoginDlg::menuCancelCallback, this));
	cancel->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/7);
	dlgMenu->addChild(cancel, 1);

	string _reg("register now!");
	reg = MenuItemFont::create(_reg, CC_CALLBACK_1(LoginDlg::menuRegCallback, this));
	reg->setPosition(origin.x + dlgSize.width/4*3, origin.y + dlgSize.height/3);
	dlgMenu->addChild(reg, 1);

	//// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(LoginDlg::menuCloseCallback, this));
	//closeItem->setPosition(Vec2(origin.x + dlgSize.width - closeItem->getContentSize().width/2 ,
	//	origin.y + closeItem->getContentSize().height/2));
	//dlgMenu->addChild(closeItem);

	//** menu 一定要在 menuItem 添加之后再 addChild **
	dlgBg->addChild(dlgMenu);

	userVerify = false;
	return true;
}

void LoginDlg::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin.", editBox);
}
 
void LoginDlg::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd.", editBox);
}
 
void LoginDlg::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
    log("editBox %p TextChanged, text: %s", editBox, text.c_str());
}
 
void LoginDlg::editBoxReturn(cocos2d::extension::EditBox *editBox)
{
    //log("editBox %p was returned.", editBox);
    // 
    //if(_editName == editBox)
    //{
    //    _TTFShowEditReturn->setString("Name EditBox return.");
    //}
    //else if (_editEmail == editBox)
    //{
    //    _TTFShowEditReturn->setString("Email EditBox return.");
    //}
}

void LoginDlg::initLabel(std::string &_intro, std::string &_name)
{
	//intro = LabelTTF::create(_intro, "", 30);
	//intro->setPosition(origin.x + dlgSize.width / 4*3, origin.y + dlgSize.height / 2);
	//dlgBg->addChild(intro);

	//name = LabelTTF::create(_name, "", 50);
	//name->setPosition(origin.x + dlgSize.width / 2, origin.y + dlgSize.height / 8*7);
	//dlgBg->addChild(name);
}

void LoginDlg::setID(std::string &_dlgID)
{
	dlgID = _dlgID;
}

void LoginDlg::menuCloseCallback(Ref* pSender)
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

void LoginDlg::menuCancelCallback(Ref* pSender)
{
	this->setVisible(false);
	sceneMenu->setEnabled(true);
}

void LoginDlg::menuRegCallback(Ref* pSender)
{
	Scene* test = HelloWorld::createScene(dlgID);
	//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
	Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
}

void LoginDlg::menuLoginCallback(Ref* pSender)
{
	if(!userVerify){
		email	= emailBox->getText();
		pwd		= passwordBox->getText();

		//log("%s\n", email);
		//log("%s\n", pwd);

		char postData[80];
		sprintf(postData, "op=client_download&data={\"email\":\"%s\",\"pwd\":\"%s\"}", email, pwd);

		requestDlg = new HttpRequest();
		requestDlg->setUrl("http://www.baidu.com");
		requestDlg->setRequestType(HttpRequest::Type::GET);

		//requestDlg->setRequestType(HttpRequest::Type::POST);
		//requestDlg->setUrl("http://192.168.1.106/php/scene_api.php");
		//requestDlg->setRequestData(postData, strlen(postData));

		requestDlg->setResponseCallback(CC_CALLBACK_2(LoginDlg::onHttpRequestComplete, this));
		requestDlg->setTag("scene");
		HttpClient::getInstance()->send(requestDlg);
		requestDlg->release();
	}
	else{

	}
}

bool LoginDlg::getUserItem()
{
	return userVerify;
}

void LoginDlg::onHttpRequestComplete(HttpClient *sender, HttpResponse* response)
{
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

	char* save = new char[buffer->size()];
	//int t=0;
	for (long i = 0; i < buffer->size(); i++)
    {
        save[i] =  (*buffer)[i];
    }
	//log("%ld", strlen(save));
	//log("%ld", t);
	//log("%s", save);
	//log("%c", save[13]);

	string load_str = string(save, buffer->size());
	
	rapidjson::Document readdoc;
	readdoc.Parse<0>(load_str.c_str());
	if(readdoc.HasParseError())
	{
		log("GetParseError%s\n", readdoc.GetParseError());
	}

	if(!readdoc.IsObject())
		return;

	rapidjson::Value& _json = readdoc["status"];
	const char* status = _json.GetString();

	// status == "OK" 时，返回值为 0
	if(!strcmp(status, "OK")){
		userVerify = true;

		this->setVisible(false);
		sceneMenu->setEnabled(true);
	}
	else{

	}

	//rapidjson::Value& _json = readdoc["u_id"];
	//const char* u_id = _json.GetString();
	//cocos2d::log(u_id);
	//cocos2d::log(_json.GetString());

	//rapidjson::Value& _json = readdoc["name"];
	//const char* name = _json.GetString();
	//cocos2d::log(name);
	//cocos2d::log(_json.GetString());

	//rapidjson::Value& _json = readdoc["avatar"];
	//const char* avatar = _json.GetString();
	//cocos2d::log(avatar);
	//cocos2d::log(_json.GetString());

	return;
}