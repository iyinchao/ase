#ifndef _DIALOGLAYER_H_
#define _DIALOGLAYER_H_

#include "cocos2d.h"

class DialogLayer: public cocos2d::LayerColor
{
public:
    /** ���еĲ˵���ťѹ�뵽������ */
    void pushMenu(cocos2d::MenuItem *pMenu);
	virtual bool init();
    virtual void onExit();
	
	void menuCloseCallback(cocos2d::Ref* pSender);
	void setSceneMenu(cocos2d::Menu* _sceneMenu);
	void setOutMenu(cocos2d::Menu* _outMenu);
	CREATE_FUNC(DialogLayer);
    
    cocos2d::EventListenerTouchOneByOne* dlistener;

protected:
    /** ��ʼ���˵� ���˵���ӵ�ģ̬�Ի����� **/
    bool initMenu();
	cocos2d::Sprite *dlgBg;
	cocos2d::Menu *dlgMenu;
	cocos2d::Menu *sceneMenu;
	cocos2d::Menu *outMenu;
	//cocos2d::Vector<cocos2d::MenuItem> menuItemArray;	// ���в˵�
    bool mTouchedMenu;									// ��¼�˵����
};

#endif