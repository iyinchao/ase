#ifndef _LOGIN_DLG_H_
#define _LOGIN_DLG_H_

#include "cocos-ext.h"
#include "DialogLayer.h"
#include "network\HttpClient.h"
#include "network\HttpRequest.h"
#include "network\HttpResponse.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"

class LoginDlg : public DialogLayer, public cocos2d::extension::EditBoxDelegate
{
public:
	virtual bool init();
	void initLabel(std::string &_intro, std::string &_name);
	void setID(std::string &_dlgID);

	// a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCancelCallback(cocos2d::Ref* pSender);
	void menuLoginCallback(cocos2d::Ref* pSender);
	void menuRegCallback(cocos2d::Ref* pSender);

	//virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    //virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
    virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
	void onHttpRequestComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *reponse);

	bool getUserItem();

	CREATE_FUNC(LoginDlg);

public:
	cocos2d::Size dlgSize;
	cocos2d::Size bgSize;
	cocos2d::Vec2 origin;
	bool userVerify;
	std::string userU_id;
	std::string userName;
	std::string userAvatar;

private:
	cocos2d::Sprite *border;
	cocos2d::Sprite *emailBg;
	cocos2d::MenuItemFont *login;
	cocos2d::MenuItemFont *cancel;
	cocos2d::MenuItemFont *reg;
	std::string dlgID;
	//cocos2d::TextFieldTTF *tf;
	cocos2d::extension::EditBox *emailBox;
	cocos2d::extension::EditBox *passwordBox;
	cocos2d::network::HttpRequest* requestDlg;

	cocos2d::MenuItemImage *userItem;
	const char* email;
	const char* pwd;
};

#endif