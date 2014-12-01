#include "ConfirmDlg.h"
#include "HelloWorldScene.h"

USING_NS_CC;
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

	//// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(ConfirmDlg::menuCloseCallback, this));
	//closeItem->setPosition(Vec2(origin.x + dlgSize.width - closeItem->getContentSize().width/2 ,
	//	origin.y + closeItem->getContentSize().height/2));
	//dlgMenu->addChild(closeItem);

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
	Scene* test = HelloWorld::createScene(dlgID);
	//Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
	Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
}