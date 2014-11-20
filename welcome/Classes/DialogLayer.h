#ifndef _DIALOGLAYER_H_
#define _DIALOGLAYER_H_

#include "cocos2d.h"

class DialogLayer: public cocos2d::LayerColor
{
public:
    /** ���еĲ˵���ťѹ�뵽������ */
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
    /** ��ʼ���˵� ���˵���ӵ�ģ̬�Ի����� **/
    bool initMenu();

private:
    cocos2d::Menu *dialogMenu;							// ģ̬�Ի���˵�
	//cocos2d::Vector<cocos2d::MenuItem> menuItemArray;	// ���в˵�
    bool mTouchedMenu;									// ��¼�˵����
};

#endif