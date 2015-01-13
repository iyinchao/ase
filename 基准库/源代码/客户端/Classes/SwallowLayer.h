//
//  SwallowLayer.h
//  HelloWorld
//
//  Created by LAB da on 14-12-31.
//
//

#ifndef __HelloWorld__SwallowLayer__
#define __HelloWorld__SwallowLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class SwallowLayer : public Layer {
private:
    EventListenerTouchOneByOne *listener;
public:
    virtual bool init();
    CREATE_FUNC(SwallowLayer);
    void remove();
    void swallow();
};

#endif /* defined(__HelloWorld__SwallowLayer__) */
