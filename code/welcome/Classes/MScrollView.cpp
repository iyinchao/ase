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
//    //创建一个结点  
//    CCNode* c = CCNode::create();  
//   
//    _contaner = c;  
//   
//    //创建5个紧挨着的精灵  
//    for(int i = 0; i < 5; i++)  
//    {  
//        CCSprite* sprite = CCSprite::create("HelloWorld.png");  
//        c->addChild(sprite);  
//           
//        //设置图片的位置，每两张图片相差一个屏幕的宽度  
//        sprite->setPosition(ccpAdd(center, ccp(i*winSize.width, 0)));  
//   
//        //给视图编号  
//        char buf[10];  
//        sprintf(buf, "%d", i);  
//        CCLabelTTF* label = CCLabelTTF::create(buf, "Arial", 36);     
//        sprite->addChild(label);  
//        label->setPosition(center);  
//    }  
//   
//    //滚动视图  
//    //第一个参数：在窗口显示的视图大小  
//    //第二个参数：结点CCNode  
//    ScrollView* view = ScrollView::create(winSize, c);  
//    addChild(view);  
//   
//    //设置视图运动的方向为水平运动  
//	view->setDirection(ScrollView::Direction::HORIZONTAL);  
//   
//    //设置视图的宽度和高度  
//    view->setContentSize(CCSize(winSize.width * 5, winSize.height * 5));  
//   
//     //取消ScrollView的弹性     
//     view->setBounceable(false);    
//   
//    //注册触摸事件  
//    setTouchEnabled(true);  
//    setTouchMode(kCCTouchesOneByOne);  
//   
//    return true;  
//}  
//   
////鼠标点下的时候  
//bool MScrollView::ccTouchBegan(CCTouch* touch, CCEvent* ev)  
//{  
//    return true;  
//}  
//   
////鼠标起来的时候  
//void MScrollView::ccTouchEnded(CCTouch* touch, CCEvent*)  
//{  
//    //得到鼠标点下去的时候的位置  
//    CCPoint ptDown = touch->getStartLocation();  
//   
//    //得到鼠标松开时的位置  
//    CCPoint ptUp = touch->getLocation();  
//   
//    //当两个位置的距离的平方小于25时(认为是点击，否则是滑动)  
//    if(ptUp.getDistanceSq(ptDown) <= 25)  
//    {  
//        //检查点击的是哪一个图片  
//        //将世界坐标转换成结点坐标  
//        CCPoint ptInContainer = _contaner->convertToNodeSpace(ptUp);  
//   
//        //定义一个数组保存5个精灵  
//        CCArray* arr = _contaner->getChildren();  
//   
//        for(int i = 0; i < 5; ++i)  
//        {  
//            //获取精灵的索引(获取点击的是哪个精灵)  
//            CCSprite* sprite = (CCSprite*)arr->objectAtIndex(i);  
//               
//            //boundingBox()获取精灵的边框(判断触摸点是否在边框内，当在的时候，打印精灵的编号)  
//            if(sprite->boundingBox().containsPoint(ptInContainer))  
//            {  
//                CCLog("click i is %d", i);  
//                break;  
//            }  
//        }  
//    }  
//    else  
//    {  
//        //滑动    
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
