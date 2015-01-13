//
//  SwallowLayer.cpp
//  HelloWorld
//
//  Created by LAB da on 14-12-31.
//
//

#include "SwallowLayer.h"

bool SwallowLayer::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
 //   _eventDispatcher->removeAllEventListeners();
 //   _eventDispatcher->removeEventListener(listener);
    
    return true;
}

void SwallowLayer::remove(){
//    CCLog("swallow\n");
 //   _eventDispatcher->setPriority(listener, 1000);
    listener->setSwallowTouches(false);
}

void SwallowLayer::swallow(){
//    CCLOG("remove\n");
  //  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
   // _eventDispatcher->setPriority(listener, 0);
    listener->setSwallowTouches(true);
}
