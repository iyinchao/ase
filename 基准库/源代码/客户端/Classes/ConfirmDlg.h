#ifndef _CONFIRM_DLG_H_
#define _CONFIRM_DLG_H_

#include "DialogLayer.h"
#include "HelloWorldScene.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

class ConfirmDlg : public DialogLayer
{
public:
	virtual bool init();
	void initLabel(std::string _intro, std::string _name);
	void setID(std::string _dlgID);

    void disappear();
    
	// a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCancelCallback(cocos2d::Ref* pSender);
	void menuDownloadCallback(cocos2d::Ref* pSender);
	void menuEnterCallback(cocos2d::Ref* pSender);
	void onHttpRequestComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *reponse);

	CREATE_FUNC(ConfirmDlg);
    virtual void onExit();

public:
	cocos2d::Size dlgSize;
	cocos2d::Size bgSize;
    cocos2d::Vec2 origin;
    cocos2d::EventListenerTouchOneByOne* listener;

private:
    bool opened;
	cocos2d::Sprite *border;
	cocos2d::Sprite *pic;
	cocos2d::Label *intro;
	cocos2d::LabelTTF *name;
	cocos2d::MenuItemFont *download;
	cocos2d::MenuItemFont *cancel;
	std::string dlgID;
	cocos2d::network::HttpRequest* requestDlg;
    
    DialogLayer* failedLayer;
    cocos2d::LabelTTF* failedTip;
    void connectFailed(float dt);
};

//ConfirmDlg : public DialogLayer::ConfirmDlg : public DialogLayer()
//{
//}
//
//ConfirmDlg : public DialogLayer::~ConfirmDlg : public DialogLayer()
//{
//}

#endif