#ifndef _CONFIRM_DLG_H_
#define _CONFIRM_DLG_H_

#include "MScrollView.h"
#include "DialogLayer.h"
#include "SearchDlg.h"
#include "ConfirmDlg.h"
#include "network\HttpClient.h"
#include "network\HttpRequest.h"
#include "network\HttpResponse.h"
#include "cocos-ext.h"
#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include <vector>

using namespace cocos2d::network;
using namespace std;
using namespace cocos2d;

class SearchDlg : public DialogLayer
{
public:
	virtual bool init();
	void initLabel(std::string _intro, std::string _name);
	//void setID(std::string _dlgID);

	// a selector callback
	void menuCancelCallback(cocos2d::Ref* pSender);
	void menuSelectCallback(cocos2d::Ref* pSender);
	void onHttpRequestComplete(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *reponse);

	CREATE_FUNC(SearchDlg);

public:
	cocos2d::Size dlgSize;
	cocos2d::Size bgSize;
	cocos2d::Vec2 origin;
	std::vector<std::string> sceneID;

private:
	//cocos2d::Sprite *border;
	//cocos2d::Sprite *pic;
	//cocos2d::Label *intro;
	cocos2d::LabelTTF *name;
	cocos2d::MenuItemFont *select;
	cocos2d::MenuItemFont *cancel;
	//std::string dlgID;
	cocos2d::network::HttpRequest* httpRequest;

	cocos2d::ui::CheckBox* bed;
	cocos2d::ui::CheckBox* carbinet;
	cocos2d::ui::CheckBox* light;
	cocos2d::ui::CheckBox* land;
	cocos2d::ui::CheckBox* table;
	cocos2d::ui::CheckBox* curtain;

	bool objectSelected[6];
	void setBedState();
	void setCarbinetState();
	void setLightState();
	void setLandState();
	void setTableState();
	void setCurtainState();

	cocos2d::ui::CheckBox* orderNamed;
	cocos2d::ui::CheckBox* orderDated;
	bool orderSelected[2];
	void setOrderNamedState();
	void setOrderDatedState();
};

#endif