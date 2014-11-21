#ifndef __MEIJIA_MAIN_SCENE_H__
#define __MEIJIA_MAIN_SCENE_H__

#include "cocos2d.h"
#define ITEMCOLS 3
#define ITEMROWS 2

class MeijiaMain : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void sceneItemCallback(cocos2d::Ref* pSender, int id);
	//virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MeijiaMain);

	void addSceneItems(cocos2d::Sprite* mainScene);

private:
	cocos2d::MenuItemImage * sceneItem[6];
	cocos2d::MenuItemImage * user;
	cocos2d::MenuItemImage * setting;
	cocos2d::Menu* menu;
};

#endif // __MEIJIA_MAIN_SCENE_H__
