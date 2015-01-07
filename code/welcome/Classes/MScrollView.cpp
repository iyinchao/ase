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
	}
    return true;  
}  

void MScrollView::initScrollView(const int _sceneNum, std::vector<std::string>& _sceneID)
{
	sceneNum	= _sceneNum;
	sceneID		= _sceneID;
	cocos2d::log(_sceneID[0].c_str());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();  
   
    CCPoint center = ccp(winSize.width / 2, winSize.height / 2); 

	//����һ�����  
    CCNode* c = CCNode::create(); 
   
    _contaner = c;  
    
	int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);
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
        sprintf(buf, "%d/%d", i + 1, sumpage);  
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36);    
		label->setString(buf);
		label->setColor(ccc3(66, 66, 66));
        sprite->addChild(label);  
		label->setPosition(Vec2(winSize.width / 2, winSize.height / 12));  
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
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36); 
		label->setString(buf);
        sprite->addChild(label);  
		label->setColor(ccc3(66, 66, 66));
        label->setPosition(Vec2(winSize.width / 2, winSize.height / 12));  
	}
   
    //������ͼ  
    //��һ���������ڴ�����ʾ����ͼ��С  
    //�ڶ������������CCNode  
    view = ScrollView::create(winSize, c);  
    addChild(view);  
   
    //������ͼ�˶��ķ���Ϊˮƽ�˶�  
	view->setDirection(ScrollView::Direction::HORIZONTAL);  
   
    //������ͼ�Ŀ�Ⱥ͸߶�  
	if(sceneNum % 6 == 0)
	{
		view->setContentSize(Size(winSize.width * (int)(sceneNum / 6), winSize.height)); 
	}
	else
	{
		view->setContentSize(Size(winSize.width * (int)(sceneNum / 6 + 1), winSize.height));  
	}
   
     //ȡ��ScrollView�ĵ���     
    view->setBounceable(false);    
   
    //ע�ᴥ���¼�  
    setTouchEnabled(true);  
    setTouchMode(kCCTouchesOneByOne);  
}

void MScrollView::setScrollInfo(std::map<std::string, std::string>& _snamemap, std::map<std::string, std::string>& _intromap)
{
	intromap.clear();
	snamemap.clear();

	intromap = _intromap;
	snamemap = _snamemap;
	return;
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
			// ��ֹ���һҳ�������� 6 ��
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