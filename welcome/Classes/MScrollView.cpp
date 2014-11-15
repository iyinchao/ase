//#include "MScrollView.h"
//   
//CCScene* MScrollView::scene()  
//{  
//    CCScene *scene = CCScene::create();  
//       
//    MScrollView *layer = MScrollView::create();  
//   
//    scene->addChild(layer);  
//   
//    return scene;  
//}  
//   
//bool MScrollView::init()  
//{  
//    CCLayer::init();  
//   
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();  
//   
//    CCPoint center = ccp(winSize.width / 2, winSize.height / 2);  
//       
//    //����һ�����  
//    CCNode* c = CCNode::create();  
//   
//    _contaner = c;  
//   
//    //����5�������ŵľ���  
//    for(int i = 0; i < 5; i++)  
//    {  
//        CCSprite* sprite = CCSprite::create("HelloWorld.png");  
//        c->addChild(sprite);  
//           
//        //����ͼƬ��λ�ã�ÿ����ͼƬ���һ����Ļ�Ŀ��  
//        sprite->setPosition(ccpAdd(center, ccp(i*winSize.width, 0)));  
//   
//        //����ͼ���  
//        char buf[10];  
//        sprintf(buf, "%d", i);  
//        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
//        sprite->addChild(label);  
//        label->setPosition(center);  
//    }  
//   
//    //������ͼ  
//    //��һ���������ڴ�����ʾ����ͼ��С  
//    //�ڶ������������CCNode  
//    ScrollView* view = ScrollView::create(winSize, c);  
//    addChild(view);  
//   
//    //������ͼ�˶��ķ���Ϊˮƽ�˶�  
//	view->setDirection(ScrollView::Direction::HORIZONTAL);  
//   
//    //������ͼ�Ŀ�Ⱥ͸߶�  
//    view->setContentSize(CCSize(winSize.width * 5, winSize.height * 5));  
//   
//     //ȡ��ScrollView�ĵ���     
//     view->setBounceable(false);    
//   
//    //ע�ᴥ���¼�  
//    setTouchEnabled(true);  
//    setTouchMode(kCCTouchesOneByOne);  
//   
//    return true;  
//}  
//   
////�����µ�ʱ��  
//bool MScrollView::ccTouchBegan(CCTouch* touch, CCEvent* ev)  
//{  
//    return true;  
//}  
//   
////���������ʱ��  
//void MScrollView::ccTouchEnded(CCTouch* touch, CCEvent*)  
//{  
//    //�õ�������ȥ��ʱ���λ��  
//    CCPoint ptDown = touch->getStartLocation();  
//   
//    //�õ�����ɿ�ʱ��λ��  
//    CCPoint ptUp = touch->getLocation();  
//   
//    //������λ�õľ����ƽ��С��25ʱ(��Ϊ�ǵ���������ǻ���)  
//    if(ptUp.getDistanceSq(ptDown) <= 25)  
//    {  
//        //�����������һ��ͼƬ  
//        //����������ת���ɽ������  
//        CCPoint ptInContainer = _contaner->convertToNodeSpace(ptUp);  
//   
//        //����һ�����鱣��5������  
//        CCArray* arr = _contaner->getChildren();  
//   
//        for(int i = 0; i < 5; ++i)  
//        {  
//            //��ȡ���������(��ȡ��������ĸ�����)  
//            CCSprite* sprite = (CCSprite*)arr->objectAtIndex(i);  
//               
//            //boundingBox()��ȡ����ı߿�(�жϴ������Ƿ��ڱ߿��ڣ����ڵ�ʱ�򣬴�ӡ����ı��)  
//            if(sprite->boundingBox().containsPoint(ptInContainer))  
//            {  
//                CCLog("click i is %d", i);  
//                break;  
//            }  
//        }  
//    }  
//    else  
//    {  
//        //����    
//        int x = _contaner->getPositionX();    
//             
//        if (x >= -1920 && x <= 0)    
//        {    
//            // adjust    
//            // 0, -480, -960, -1440, -1920    
//            int idx = (-x +240)/ 480;    
//            x = -idx * 480;    
//     
//            CCMoveTo* moveTo = CCMoveTo::create(0.5f, ccp(x, this->_contaner->getPositionY()));    
//                 
//            this->_contaner->runAction(moveTo);    
//        }    
//    }    
//}
