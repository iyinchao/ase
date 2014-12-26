#include "MScrollView.h"
#include "ConfirmDlg.h"

CCScene* MScrollView::scene()  
{  
    CCScene *scene = CCScene::create();  
       
    MScrollView *layer = MScrollView::create();  
   
    scene->addChild(layer);  
   
    return scene;  
}  

//static MScrollView* MScrollView::createScroll(const int _sceneNum)
//{ 
//	MScrollView *pRet = new MScrollView();
//	pRet->sceneNum = _sceneNum;
//    if (pRet && pRet->init())
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    else
//    {
//        delete pRet;
//        pRet = NULL;
//        return NULL;
//    }
//}

bool MScrollView::init()  
{  
    CCLayer::init();  
	//this->setAnchorPoint(Vec2(0, 0));
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
   
    _contaner = c;  
    
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
        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
        sprite->addChild(label);  
		label->setPosition(Vec2(winSize.width / 2, winSize.height / 8));  
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
        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
        sprite->addChild(label);  
        label->setPosition(Vec2(winSize.width / 2, winSize.height / 8));  
	}
   
    //滚动视图  
    //第一个参数：在窗口显示的视图大小  
    //第二个参数：结点CCNode  
    view = ScrollView::create(winSize, c);  
    addChild(view);  
   
    //设置视图运动的方向为水平运动  
	view->setDirection(ScrollView::Direction::HORIZONTAL);  
   
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
   
//鼠标点下的时候  
bool MScrollView::onTouchBegan(Touch* touch, Event* event)  
{  
	//得到鼠标点下去的时候的位置  
    ptDown = touch->getStartLocation();  
    return true;  
}  
   
//鼠标起来的时候  
void MScrollView::onTouchEnded(Touch* touch, Event* event)  
{  
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    ////得到鼠标点下去的时候的位置  
    //Point ptDown = touch->getStartLocation();  
   
    //得到鼠标松开时的位置  
    Point ptUp = touch->getLocation();  
   
    //当两个位置的距离的平方小于25时(认为是点击，否则是滑动)  
	if(pow(ptUp.x - ptDown.x, 2) <= 16)  
    {  
  //      //检查点击的是哪一个图片  
  //      //将世界坐标转换成结点坐标  
  //      Point ptInContainer = _contaner->convertToNodeSpace(ptUp);  
  // 
  //      //定义一个数组保存5个精灵  
		//Vector<Node*> arr = _contaner->getChildren();  
  // 
  //      for(int i = 0; i < 5; ++i)  
  //      {  
  //          // 获取精灵的索引(获取点击的是哪个精灵)  
		//	CCSprite* sprite = (CCSprite*)arr.at(i);  
  //             
  //          //boundingBox()获取精灵的边框(判断触摸点是否在边框内，当在的时候，打印精灵的编号)  
  //          if(sprite->boundingBox().containsPoint(ptInContainer))  
  //          {  
  //              CCLog("click i is %d", i);  
  //              break;  
  //          }  
  //      }  
    }  
    else  
    {  
        //滑动    
        int x = _contaner->getPositionX();    
             
		if (x >= -(int)(sceneNum / 6 + 1) * winSize.width && x <= 0)    
        {    
            // adjust    
            // 0, -1024, -2048, -3072, -4096    
            int idx = (-x + winSize.width/2)/ winSize.width;    
            x = -idx * winSize.width;    
     
            MoveTo* moveTo = MoveTo::create(0.2f, ccp(x, this->_contaner->getPositionY()));    
                 
            this->_contaner->runAction(moveTo);    
        }    
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

	//switch(id){
	//case 0:
	//	//layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//case 1:
	//	//layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//case 2:
	//	//layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//case 3:
	//	//layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//case 4:
	//	layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//case 5:
	//	layertest = ConfirmDlg::create();
	//	_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
	//	layertest->setID(_dlgID);
	//	break;
	//default:
	//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	//	return;
	//}

	// CCLOG(_dlgID);
	layertest->initLabel(intro, titlestr);

	//auto tmpMenu = Menu::create(outMenu, menu);
	//layertest->setSceneMenu(menu);
	layertest->setOutMenu(outMenu);
	this->addChild(layertest, 10);
	//menu->setEnabled(false);
	//outMenu->setEnabled(false);
	return;
}

void MScrollView::setOutMenu(cocos2d::Menu* _outMenu)
{
	outMenu = _outMenu;
}