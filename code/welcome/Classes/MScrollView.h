#ifndef __MSCROLL_VIEW_H__  
#define __MSCROLL_VIEW_H__  
   
#include "cocos2d.h"  
#include "cocos-ext.h"  
USING_NS_CC;  
USING_NS_CC_EXT;  

#define SCENESUM 8
#define ITEMCOLS 3
#define ITEMROWS 2
   
class MScrollView : public Layer  
{  
public:  
    virtual bool init();
	//void sceneBorderCallback(cocos2d::Ref* pSender, int id, cocos2d::Menu* menu);
	void sceneBorderCallback(cocos2d::Ref* pSender, int id, cocos2d::Menu* menu);
	void menuSearchCallback(cocos2d::Ref* pSender);
   
    static Scene* scene();  
       
	CREATE_FUNC(MScrollView);  
	//static MScrollView* createScroll(const int sceneNum);
	void addSceneBorder(cocos2d::Sprite* mainScene, int itemrows, int itemcols, int page, int itemnum);
	void addScenePic(cocos2d::Sprite* mainScene, int itemrows, int itemcols, int page, int itemnum);
   
    //ÏìÓ¦´¥ÃþÊÂ¼þ  
	bool onTouchBegan(Touch* Touch, Event* Event);  
    void onTouchEnded(Touch* Touch, Event* Event); 

	void setOutMenu(cocos2d::Menu* _outMenu);
	void initScrollView(const int _sceneNum, std::vector<std::string>& _sceneID);
	void setScrollInfo(std::map<std::string, std::string>& _snamemap, std::map<std::string, std::string>& _intromap);

	cocos2d::Menu* menu;

private:
	cocos2d::Menu* outMenu;
	cocos2d::MenuItemImage * sceneBorder[6];
	cocos2d::Sprite * scenePic[6];
	cocos2d::MenuItemImage * searchItem;
	Point ptDown;
    Node* _contaner;
	int sceneNum;
	std::vector<std::string> sceneID;
	std::map<std::string, std::string> intromap;
	std::map<std::string, std::string> snamemap;
	cocos2d::extension::ScrollView* view;
	//cocos2d::LabelTTF* label;
};  
   
#endif // __ScrollView_H__
