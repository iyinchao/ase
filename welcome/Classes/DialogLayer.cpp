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

    CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);

    //CCMenuItemFont *okMenuItem = MenuItemFont::create("OK", this, menu_selector(ExitDlg::okMenuItemCallback));
    //okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));

    //CCMenuItemFont *cancelMenuItem = MenuItemFont::create("Cancel", this, menu_selector(ExitDlg::cancelMenuItemCallback));
    //cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));

	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DialogLayer::menuCloseCallback, this));
	
	dialogMenu = Menu::create(closeItem, NULL);
	dialogMenu->setPosition(CCPointZero);
	this->addChild(dialogMenu);
	//dialogMenu->setTouchEnabled(true);

    //pushMenu(okMenuItem);
    //pushMenu(cancelMenuItem);

    return true;
}

void DialogLayer::menuCloseCallback(Ref *pSender)
{
	Director::getInstance()->end();
}

//void DialogLayer::onEnter()
//{
//    CCLayerColor::onEnter();
//	Director::getInstance()->
//		sharedDirector()->
//	TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority - 1, true);
//}
//
//void DialogLayer::onExit()
//{
//    CCLayerColor::onExit();
//    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
//}
//
//bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
//    
//    return true;
//}
//
//void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        m_pMenu->ccTouchMoved(pTouch, pEvent);
//    }
//}
//
//void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        m_pMenu->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
//    }
//}
//
//void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    if (m_bTouchedMenu) {
//        m_pMenu->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
//    }
//}
//
//void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
//{
//    // 鐐瑰嚮纭畾灏遍��鍑猴紙鎷疯礉鐨勫師鏈夋柟娉曪級
//    CCDirector::sharedDirector()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
//}
//
//void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
//{
//    this->removeFromParentAndCleanup(false);
//}
