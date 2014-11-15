#include "MeijiaMainScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MeijiaMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MeijiaMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MeijiaMain::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "SettingNormal.png",
                                           "SettingSelected.png",
                                           CC_CALLBACK_1(MeijiaMain::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 - 10,
                                origin.y + closeItem->getContentSize().height/2 + 10));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);

    //auto label = LabelTTF::create("meijia", "Arial", 80);
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height/4*3));
	//this->addChild(label, 1);

	auto mainBg = Sprite::create("MainBg.png", Rect(0, 0, 1024, 768));
	mainBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	auto voidBg = Sprite::create("voidBg.png");
	voidBg->setPosition(mainBg->getContentSize().width/2, mainBg->getContentSize().height/2);
	addSceneItems(voidBg, menu);

	mainBg->addChild(voidBg, 0);
	voidBg->addChild(menu, 0);

    // add the sprite as a child to this layer
    this->addChild(mainBg, 0);
    
    return true;
}

void MeijiaMain::addSceneItems(Sprite* mainScene, Menu* menu)
{
	int index;
	for(int i=0; i<ITEMROWS; i++)
		for(int j=0; j<ITEMCOLS; j++)
		{
			index = i*ITEMCOLS + j;
			sceneItem[index] = MenuItemImage::create(
												"BorderNormal.png",
												"BorderSelected.png",
												CC_CALLBACK_1(MeijiaMain::sceneItemCallback, this, index));
												//CC_CALLBACK_1(MeijiaMain::menuCloseCallback, this));
			sceneItem[index]->setScale(2.f);
			sceneItem[index]->setPosition(Vec2( mainScene->getContentSize().width/(ITEMCOLS+1)*(j+1),
					mainScene->getContentSize().height/(ITEMROWS+1)*(i+1)));

			menu->addChild(sceneItem[index], 1);
		}

	//// 预留接口在边框内添加文字、缩略图等
	//auto label = LabelTTF::create("meijia", "Arial", 80);
	//label->setPosition(Vec2(sceneItem[0]->getPosition().x, sceneItem[0]->getPosition().y));
	//menu->addChild(label, 0);
}

void MeijiaMain::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MeijiaMain::sceneItemCallback(cocos2d::Ref* pSender, int id)
{
	Scene* test;
	switch(id){
	case 0:
		test = HelloWorld::createScene("test 1");
		break;
	case 1:
		test = HelloWorld::createScene("test 2");
		break;
	case 2:
		test = HelloWorld::createScene("test 3");
		break;
	case 3:
		test = HelloWorld::createScene("test 4");
		break;
	case 4:
		test = HelloWorld::createScene("test 5");
		break;
	case 5:
		test = HelloWorld::createScene("test 6");
		break;
	default:
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	}
	// Director::getInstance()->replaceScene(TransitionFade::create(1.f, test));
	Director::getInstance()->pushScene(TransitionFade::create(1.f, test));
	
	//Director::getInstance()->end();
}