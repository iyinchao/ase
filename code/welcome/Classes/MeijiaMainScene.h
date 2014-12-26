#ifndef __MEIJIA_MAIN_SCENE_H__
#define __MEIJIA_MAIN_SCENE_H__

#include "cocos2d.h"
#include "network\HttpClient.h"
#include "network\HttpRequest.h"
#include "network\HttpResponse.h"
#include "LoginDlg.h"
#include "MScrollView.h"
#include "SearchDlg.h"
#include "cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CocoStudio.h"

#define SCENESUM 9
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
    void menuSearchCallback(cocos2d::Ref* pSender);
	void sceneBorderCallback(cocos2d::Ref* pSender, int id);
	void menuLoginCallback(cocos2d::Ref* pSender);
	void onHttpRequestComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *reponse);

	//virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MeijiaMain);
	void addSceneBorder(cocos2d::Layer* mainScene);
	void addScenePic(cocos2d::Layer* mainScene);
	void addScrollView(int _sceneNum, std::vector<std::string>& _test);

	cocos2d::Texture2D* Base64toTex(std::string bfile);
	void updateCustom(float dt);

public:
	cocos2d::MenuItemImage * userItem;
	bool userVerify;
	cocos2d::Menu* menu;
	MScrollView* voidBg;
	cocos2d::Sprite* mainBg;
	int sceneNum;

private:
	cocos2d::MenuItemImage * sceneBorder[6];
	cocos2d::Sprite * scenePic[6];
	cocos2d::MenuItemImage * settingItem;
	cocos2d::network::HttpRequest* request;
	LoginDlg *logintest;
	SearchDlg *searchtest;
};

#endif // __MEIJIA_MAIN_SCENE_H__
