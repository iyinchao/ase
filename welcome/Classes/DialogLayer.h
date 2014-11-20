#ifndef _DIALOGLAYER_H_
#define _DIALOGLAYER_H_

#include "cocos2d.h"

class DialogLayer: public cocos2d::LayerColor
{
public:
    /** 所有的菜单按钮压入到容器中 */
    void pushMenu(cocos2d::MenuItem *pMenu);
	virtual bool init();

    //virtual void onEnter();
    //virtual void onExit();

    //virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(DialogLayer);

private:
    /** 初始化菜单 将菜单添加到模态对话框上 **/
    bool initMenu();

private:
    cocos2d::Menu *dialogMenu;							// 模态对话框菜单
	//cocos2d::Vector<cocos2d::MenuItem> menuItemArray;	// 所有菜单
    bool mTouchedMenu;									// 记录菜单点击
};

#endif