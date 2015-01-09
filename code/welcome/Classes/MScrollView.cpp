#include "MScrollView.h"
#include "ConfirmDlg.h"
#include "MeijiaMainScene.h"
#include "SearchDlg.h"

CCScene* MScrollView::scene()  
{  
    CCScene *scene = CCScene::create();  
       
    MScrollView *layer = MScrollView::create();  
   
    scene->addChild(layer);  
   
    return scene;  
}  

bool MScrollView::init()  
{  
    CCLayer::init();  
	sceneNum = SCENESUM;

	for(int i=0; i<sceneNum; i++)
	{
		intromap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "intro\nintro\nintro\nintro\n"));
		snamemap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "TITLE"));
		mdatemap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "date"));
		designermap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "designer"));
	}

	// ************ 触摸吞噬 ************
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MScrollView::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MScrollView::onTouchEnded, this);
//	listener->onTouchMoved = [&](Touch *touch, Event *event){  
//		float start, end; 
//        start = touch->getStartLocation().x;  
//        end = touch->getLocation().x;  
//		float offset = end - start;  
//		//view->setContentOffset(Vec2(current_offset + offset * 2, 0)); 
//
//		//当两个位置的距离的平方小于25时(认为是点击，否则是滑动)  
//		if(pow(offset, 2) >= 16)  
//		{ 
//			//滑动    
//			int x = _contaner->getPositionX();         
//			int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);
//
//			if (x >= -(sumpage-1) * 1024 && x <= 0)    
//			{    
//				// adjust    
//				// 0, -1024, -2048, -3072, -4096    
//				//int idx = (-x + winSize.width/2)/ winSize.width; 
//				int idx = (-x + 512) / 1024;
//				//x = -idx * winSize.width;  
//				x = -idx * 1024;
//			}
//			else if(x >=0)
//			{
//				x = 0;
//			}
//			else
//			{
//				x = -(sumpage-1) * 1024;
//			}
//     
///*			MoveTo* moveTo = MoveTo::create(0.001f, ccp(x, this->_contaner->getPositionY()));    
//			this->_contaner->runAction(moveTo); */   
//			view->setContentOffsetInDuration(Vec2(x, this->_contaner->getPositionY()), 0.001f);
//		} 
//	}; 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;  
}  

void MScrollView::initScrollView(const int _sceneNum, std::vector<std::string>& _sceneID)
{
	sceneNum	= _sceneNum;
	sceneID		= _sceneID;
	cocos2d::log(_sceneID[0].c_str());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();  
   
    CCPoint center = ccp(winSize.width / 2, winSize.height / 2); 

	//创建一个结点  
    CCNode* c = CCNode::create(); 
    
	int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);
	for(int i = 0; i < (int)(sceneNum / 6); i++)  
    {  
		Sprite* sprite = Sprite::create("voidBg.png");
		//sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);  
           
        //设置图片的位置，每两张图片相差一个屏幕的宽度  
        sprite->setPosition(ccpAdd(center, ccp(i*winSize.width, 0)));  
		addSceneBorder(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
		addScenePic(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
   
        //给视图编号  
        char buf[10];  
        sprintf(buf, "%d/%d", i + 1, sumpage);  
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36);    
		label->setString(buf);
		label->setColor(ccc3(66, 66, 66));
        sprite->addChild(label);  
		label->setPosition(Vec2(winSize.width / 2, winSize.height / 12));  
    }  

	// 防止出现最后一页填不满
	if(sceneNum - sceneNum/6*6 > 0){
		Sprite* sprite = Sprite::create("voidBg.png");
		//sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);  
           
        //设置图片的位置，每两张图片相差一个屏幕的宽度  
        sprite->setPosition(ccpAdd(center, ccp(sceneNum/6 * winSize.width, 0)));  
		addSceneBorder(sprite, ITEMROWS, ITEMCOLS, sceneNum/6, sceneNum - sceneNum/6*6);
		addScenePic(sprite, ITEMROWS, ITEMCOLS,sceneNum/6, sceneNum - sceneNum/6*6);
   
        //给视图编号  
        char buf[10];  
        sprintf(buf, "%d/%d", sceneNum/6 + 1, (int)(sceneNum / 6 + 1));  
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36); 
		label->setString(buf);
        sprite->addChild(label);  
		label->setColor(ccc3(66, 66, 66));
        label->setPosition(Vec2(winSize.width / 2, winSize.height / 12));  
	}
   
    //滚动视图  
    //第一个参数：在窗口显示的视图大小  
    //第二个参数：结点CCNode  
    //view = ScrollView::create(winSize, c);
	c->setContentSize(CCSizeMake(sumpage* winSize.width, winSize.height));
    _contaner = c;  

	view = ScrollView::create(CCSizeMake(1024, 768), c);
	view->setContentOffset(CCPointZero);
	//设置视图运动的方向为水平运动  
	view->setDirection(ScrollView::Direction::HORIZONTAL); 
	view->setPosition(CCPointZero);
    this->addChild(view);  
   
    //设置视图的宽度和高度  
	if(sceneNum % 6 == 0)
	{
		view->setContentSize(Size(winSize.width * (int)(sceneNum / 6), winSize.height)); 
	}
	else
	{
		view->setContentSize(Size(winSize.width * (int)(sceneNum / 6 + 1), winSize.height));  
	}
   
     //取消ScrollView的弹性     
    view->setBounceable(false);    
   
    //注册触摸事件  
    setTouchEnabled(true);  
    setTouchMode(kCCTouchesOneByOne);  
}

void MScrollView::setScrollInfo(
		std::map<std::string, std::string>& _snamemap, 
		std::map<std::string, std::string>& _intromap,
		std::map<std::string, std::string>& _designermap,
		std::map<std::string, std::string>& _mdatemap)
{
	intromap.clear();
	snamemap.clear();
	designermap.clear();
	mdatemap.clear();

	intromap = _intromap;
	snamemap = _snamemap;
	designermap = _designermap;
	mdatemap = _mdatemap;
	return;
}
   
//鼠标点下的时候  
bool MScrollView::onTouchBegan(Touch* touch, Event* event)  
{  
	//得到鼠标点下去的时候的位置  
    ptDown = touch->getStartLocation();  
    return true;  
}  

//void MScrollView::onTouchMoved(Touch* touch, Event* event)  
//{  
//	//得到鼠标点下去的时候的位置  
//    ptDown = touch->getStartLocation();  
//    // return true;  
//} 
   
//鼠标起来的时候  
void MScrollView::onTouchEnded(Touch* touch, Event* event)  
{  
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    ////得到鼠标点下去的时候的位置  
    //Point ptDown = touch->getStartLocation();  
   
    //得到鼠标松开时的位置  
    Point ptUp = touch->getLocation();  
   
    //当两个位置的距离的平方小于25时(认为是点击，否则是滑动)  
	if(pow(ptUp.x - ptDown.x, 2) >= 16)  
	{ 
        //滑动    
        int x = _contaner->getPositionX();         
		int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);

		if (x >= -(sumpage-1) * winSize.width && x <= 0)    
        {    
            // adjust    
            // 0, -1024, -2048, -3072, -4096    
            //int idx = (-x + winSize.width/2)/ winSize.width; 
			int idx = (-x + 512) / 1024;
            //x = -idx * winSize.width;  
			x = -idx * 1024;
		}
		else if(x >=0)
		{
			x = 0;
		}
		else
		{
			x = -(sumpage-1) * winSize.width;
		}
     
        MoveTo* moveTo = MoveTo::create(0.001f, ccp(x, this->_contaner->getPositionY()));    
        this->_contaner->runAction(moveTo);    
		view->setContentOffsetInDuration(Vec2(x, this->_contaner->getPositionY()), 0.001f);

		//if(ptUp.x - ptDown.x > 0)
		//{
		//	if(x >= 0) x = 0;
		//	if(x <= )
		//	MoveTo* moveTo = MoveTo::create(0.001f, ccp(x, this->_contaner->getPositionY()));    
  //          this->_contaner->runAction(moveTo); 
		//}
    }    
}

void MScrollView::addSceneBorder(Sprite* sprite, int itemrows, int itemcols, int page, int itemnum)
{
	menu = Menu::create();
	int index;
	index += (page - 1) * 6;
	for(int i=0; i<itemrows; i++)
		for(int j=0; j<itemcols; j++)
		{
			index = i*itemcols + j;

			sceneBorder[index] = MenuItemImage::create(
												"BorderNormal.png",
												"BorderSelected.png",
												//CC_CALLBACK_2(MScrollView::sceneBorderCallback, this, index, menu));
												CC_CALLBACK_1(MScrollView::sceneBorderCallback, this, index, menu));
			sceneBorder[index]->setScale(0.9f);
			sceneBorder[index]->setPosition(Vec2( sprite->getContentSize().width/(itemcols+1)*(j+1),
				sprite->getContentSize().height - sprite->getContentSize().height/(itemrows+1)*(i+1) ));

			// 防止最后一页不够放满 6 个
			if(index+1 > itemnum) continue;
			menu->addChild(sceneBorder[index], 1);
		}

	//menu->setPosition(sprite->getContentSize().width/2, sprite->getContentSize().height/2);
	menu->setPosition(Vec2(0, 0));
	sprite->addChild(menu);
	
	//// 预留接口在边框内添加文字、缩略图等
	//auto label = LabelTTF::create("meijia", "Arial", 80);
	//label->setPosition(Vec2(sceneItem[0]->getPosition().x, sceneItem[0]->getPosition().y));
	//menu->addChild(label, 0);
	return;
}

void MScrollView::addScenePic(Sprite* sprite, int itemrows, int itemcols, int page, int itemnum)
{
	int index = 0;
    if(index+1 <= itemnum){
		//scenePic[0] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		//scenePic[0] = Sprite::create(sceneID[(page-1)*6 + index] + ".jpg");
		scenePic[0] = Sprite::create(sceneID[0] + ".jpg");
		log(sceneID[0].c_str());
		index++;
	}
    if(index+1 <= itemnum){
		scenePic[1] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		index++;
	}
    if(index+1 <= itemnum){
		scenePic[2] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		index++;
	}
    if(index+1 <= itemnum){
		scenePic[3] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		index++;
	}
    if(index+1 <= itemnum){
		scenePic[4] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		index++;
	}
    if(index+1 <= itemnum){
		scenePic[5] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
		index++;
	}

	for(int i=0; i<itemrows; i++)
		for(int j=0; j<itemcols; j++)
		{
			index = i*itemcols + j;
			// 防止最后一页不够放满 6 个
			if(index+1 > itemnum) return;

			//scenePic[index] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
			scenePic[index]->setPosition(sceneBorder[index]->getPosition().x, sceneBorder[index]->getPosition().y);

			sprite->addChild(scenePic[index], 0);
		}

	return;
}

void MScrollView::sceneBorderCallback(cocos2d::Ref* pSender, int id, cocos2d::Menu* menu)
{
	ConfirmDlg *layertest = ConfirmDlg::create();
	std::string _dlgID;
	std::string titlestr("TITLE");
	std::string intro("intro\nintro\nintro\nintro\n");

//// ***** new *****
	layertest->setID(sceneID[id]);

	//map<string, string> intromap;
	//for(int i=0; i<sceneNum; i++)
	//{
	//	intromap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "intro"));
	//}

	// CCLOG(_dlgID);
	//layertest->initLabel(intro, titlestr);
	layertest->initLabel(intromap[sceneID[id]], titlestr);
	//layertest->initLabel(((MeijiaMain*)this->getParent())->intro[sceneID[id]], ((MeijiaMain*)this->getParent())->sname[sceneID[id]]);

	layertest->setOutMenu(outMenu);
	this->addChild(layertest, 10);
	return;
}

void MScrollView::setOutMenu(cocos2d::Menu* _outMenu)
{
	outMenu = _outMenu;
}