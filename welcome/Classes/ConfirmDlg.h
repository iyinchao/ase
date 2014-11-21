#ifndef _CONFIRM_DLG_H_
#define _CONFIRM_DLG_H_

#include "DialogLayer.h"

class ConfirmDlg : public DialogLayer
{
public:
	virtual bool init();
	void initLabel(std::string &_intro, std::string &_name);
	void setID(std::string &_dlgID);

	// a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCancelCallback(cocos2d::Ref* pSender);
	void menuDownloadCallback(cocos2d::Ref* pSender);
	void menuEnterCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ConfirmDlg);

public:
	cocos2d::Size dlgSize;
	cocos2d::Size bgSize;
	cocos2d::Vec2 origin;

private:
	cocos2d::Sprite *border;
	cocos2d::LabelTTF *intro;
	cocos2d::LabelTTF *name;
	cocos2d::MenuItemFont *download;
	cocos2d::MenuItemFont *cancel;
	std::string dlgID;
};

//ConfirmDlg : public DialogLayer::ConfirmDlg : public DialogLayer()
//{
//}
//
//ConfirmDlg : public DialogLayer::~ConfirmDlg : public DialogLayer()
//{
//}

#endif