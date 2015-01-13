//
//  mySprite.cpp
//  HelloWorld
//
//  Created by LAB da on 14-12-1.
//
//

#include "mySprite.h"

mySprite::mySprite(float imorder):myOrder(imorder)
{
}

bool mySprite::initWithTex(Texture2D *t){
    this->initWithTexture(t);
}

void mySprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    
    if(_insideBounds)
    {
        _quadCommand.init(myOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform);
        renderer->addCommand(&_quadCommand);
#if CC_SPRITE_DEBUG_DRAW
        _customDebugDrawCommand.init(_globalZOrder);
        _customDebugDrawCommand.func = CC_CALLBACK_0(Sprite::drawDebugData, this);
        renderer->addCommand(&_customDebugDrawCommand);
#endif //CC_SPRITE_DEBUG_DRAW
    }
}
