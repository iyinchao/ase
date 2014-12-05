#include "DialogLayer.h"

USING_NS_CC;

bool DialogLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)))
		return false;

	//** CCLayerColor不同于Layer, 默认占满整个屏幕，设置颜色和透明度即可 **
	setColor(ccc3(88, 88, 88));
    setOpacity(128);
     
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	dlgMenu = Menu::create();
	dlgMenu->setPosition(CCPointZero);
	
	dlgBg = Sprite::create("DialogBg.png");
	dlgBg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(dlgBg);

    //CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "", 64);
    //label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    //this->addChild(label);

	//auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(DialogLayer::menuCloseCallback, this));
	//closeItem->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
	//dlgMenu->addChild(closeItem);
	
    //pushMenu(okMenuItem);
    //pushMenu(cancelMenuItem);

	//** menu 一定要在 menuItem 添加之后再 addChild **
	//this->addChild(dlgMenu);
    return true;
}

void DialogLayer::menuCloseCallback(Ref *pSender)
{
	Director::getInstance()->end();
	return;
}

void DialogLayer::setSceneMenu(Menu *_sceneMenu)
{
	sceneMenu = _sceneMenu;
	return;
}