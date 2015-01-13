//
//  mySprite.h
//  HelloWorld
//
//  Created by LAB da on 14-12-1.
//
//

#ifndef __HelloWorld__mySprite__
#define __HelloWorld__mySprite__

#include "cocos2d.h"
#include "screenCapture.h"
#include "exrTexture.h"

USING_NS_CC;

class mySprite : public Sprite{
public:
    float myOrder;
    
    mySprite(float imorder);
    bool initWithTex(Texture2D *t);
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
};

#endif /* defined(__HelloWorld__mySprite__) */
