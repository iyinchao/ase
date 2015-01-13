#include "DialogLayer.h"

USING_NS_CC;

bool DialogLayer::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)))
		return false;

	//** CCLayerColor不同于Layer, 默认占满整个屏幕，设置颜色和透明度即可 **
	setColor(ccc3(44, 44, 44));
    setOpacity(200);
     
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	dlgMenu = Menu::create();
	dlgMenu->setPosition(CCPointZero);
	
	dlgBg = Sprite::create("DialogBG.png");
	dlgBg->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(dlgBg);
    
    return true;
}

void DialogLayer::onExit(){
    Layer::onExit();
    if(dlistener)
    {
        _eventDispatcher->removeEventListener(dlistener);
    }
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

void DialogLayer::setOutMenu(Menu *_outMenu)
{
	outMenu = _outMenu;
	return;
}