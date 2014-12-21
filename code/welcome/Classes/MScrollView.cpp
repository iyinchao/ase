#include "MScrollView.h"
#include "ConfirmDlg.h"

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
	//this->setAnchorPoint(Vec2(0, 0));
	sceneNum = SCENESUM;

	initScrollView();
    return true;  
}  

void MScrollView::initScrollView()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();  
   
    CCPoint center = ccp(winSize.width / 2, winSize.height / 2); 

	//����һ�����  
    CCNode* c = CCNode::create(); 
   
    _contaner = c;  
    
	for(int i = 0; i < (int)(sceneNum / 6); i++)  
    {  
		Sprite* sprite = Sprite::create("voidBg.png");
		//sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);  
           
        //����ͼƬ��λ�ã�ÿ����ͼƬ���һ����Ļ�Ŀ��  
        sprite->setPosition(ccpAdd(center, ccp(i*winSize.width, 0)));  
		addSceneBorder(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
		addScenePic(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
   
        //����ͼ���  
        char buf[10];  
        sprintf(buf, "%d/%d", i + 1, (int)(sceneNum / 6 + 1));  
        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
        sprite->addChild(label);  
        label->setPosition(center);  
    }  

	// ��ֹ�������һҳ���
	if(sceneNum - sceneNum/6*6 > 0){
		Sprite* sprite = Sprite::create("voidBg.png");
		//sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);  
           
        //����ͼƬ��λ�ã�ÿ����ͼƬ���һ����Ļ�Ŀ��  
        sprite->setPosition(ccpAdd(center, ccp(sceneNum/6 * winSize.width, 0)));  
		addSceneBorder(sprite, ITEMROWS, ITEMCOLS, sceneNum/6, sceneNum - sceneNum/6*6);
		addScenePic(sprite, ITEMROWS, ITEMCOLS,sceneNum/6, sceneNum - sceneNum/6*6);
   
        //����ͼ���  
        char buf[10];  
        sprintf(buf, "%d/%d", sceneNum/6 + 1, (int)(sceneNum / 6 + 1));  
        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
        sprite->addChild(label);  
        label->setPosition(center);  
	}
   
    //������ͼ  
    //��һ���������ڴ�����ʾ����ͼ��С  
    //�ڶ������������CCNode  
    view = ScrollView::create(winSize, c);  
    addChild(view);  
   
    //������ͼ�˶��ķ���Ϊˮƽ�˶�  
	view->setDirection(ScrollView::Direction::HORIZONTAL);  
   
    //������ͼ�Ŀ�Ⱥ͸߶�  
    view->setContentSize(Size(winSize.width * (int)(sceneNum / 6 + 1), winSize.height));  
   
     //ȡ��ScrollView�ĵ���     
    view->setBounceable(false);    
   
    //ע�ᴥ���¼�  
    setTouchEnabled(true);  
    setTouchMode(kCCTouchesOneByOne);  
}
   
//�����µ�ʱ��  
bool MScrollView::onTouchBegan(Touch* touch, Event* event)  
{  
	//�õ�������ȥ��ʱ���λ��  
    ptDown = touch->getStartLocation();  
    return true;  
}  
   
//���������ʱ��  
void MScrollView::onTouchEnded(Touch* touch, Event* event)  
{  
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    ////�õ�������ȥ��ʱ���λ��  
    //Point ptDown = touch->getStartLocation();  
   
    //�õ�����ɿ�ʱ��λ��  
    Point ptUp = touch->getLocation();  
   
    //������λ�õľ����ƽ��С��25ʱ(��Ϊ�ǵ���������ǻ���)  
	if(pow(ptUp.x - ptDown.x, 2) <= 16)  
    {  
  //      //�����������һ��ͼƬ  
  //      //����������ת���ɽ������  
  //      Point ptInContainer = _contaner->convertToNodeSpace(ptUp);  
  // 
  //      //����һ�����鱣��5������  
		//Vector<Node*> arr = _contaner->getChildren();  
  // 
  //      for(int i = 0; i < 5; ++i)  
  //      {  
  //          // ��ȡ���������(��ȡ��������ĸ�����)  
		//	CCSprite* sprite = (CCSprite*)arr.at(i);  
  //             
  //          //boundingBox()��ȡ����ı߿�(�жϴ������Ƿ��ڱ߿��ڣ����ڵ�ʱ�򣬴�ӡ����ı��)  
  //          if(sprite->boundingBox().containsPoint(ptInContainer))  
  //          {  
  //              CCLog("click i is %d", i);  
  //              break;  
  //          }  
  //      }  
    }  
    else  
    {  
        //����    
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
	for(int i=0; i<itemrows; i++)
		for(int j=0; j<itemcols; j++)
		{
			index = i*itemcols + j;

			sceneBorder[index] = MenuItemImage::create(
												"BorderNormal.png",
												"BorderSelected.png",
												//CC_CALLBACK_2(MScrollView::sceneBorderCallback, this, index, menu));
												CC_CALLBACK_1(MScrollView::sceneBorderCallback, this, index, menu));
			// sceneBorder[index]->setScale(2.f);
			sceneBorder[index]->setPosition(Vec2( sprite->getContentSize().width/(itemcols+1)*(j+1),
				sprite->getContentSize().height - sprite->getContentSize().height/(itemrows+1)*(i+1) ));

			// ��ֹ���һҳ�������� 6 ��
			if(index+1 > itemnum) continue;
			menu->addChild(sceneBorder[index], 1);
		}

	//menu->setPosition(sprite->getContentSize().width/2, sprite->getContentSize().height/2);
	menu->setPosition(Vec2(0, 0));
	sprite->addChild(menu);
	
	//// Ԥ���ӿ��ڱ߿���������֡�����ͼ��
	//auto label = LabelTTF::create("meijia", "Arial", 80);
	//label->setPosition(Vec2(sceneItem[0]->getPosition().x, sceneItem[0]->getPosition().y));
	//menu->addChild(label, 0);
	return;
}

void MScrollView::addScenePic(Sprite* sprite, int itemrows, int itemcols, int page, int itemnum)
{
	int index;
	for(int i=0; i<itemrows; i++)
		for(int j=0; j<itemcols; j++)
		{
			index = i*itemcols + j;
			// ��ֹ���һҳ�������� 6 ��
			if(index+1 > itemnum) return;

			scenePic[index] = Sprite::create("6d05d6ba-4ca2-523c-8a15-adbbfe4f2265.jpg");
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
	switch(id){
	case 0:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 1:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 2:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 3:
		//layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 4:
		layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	case 5:
		layertest = ConfirmDlg::create();
		_dlgID = "6d05d6ba-4ca2-523c-8a15-adbbfe4f2265";
		layertest->setID(_dlgID);
		break;
	default:
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	}

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