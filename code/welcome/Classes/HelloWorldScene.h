#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	std::string folderName;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(std::string tag);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(std::string tag);  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
