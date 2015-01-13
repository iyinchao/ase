#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio;
using namespace ui;

Scene* HelloWorld::createScene(std::string tag, std::string name, std::string intro)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = new HelloWorld();
    if (layer && layer->init(tag,name,intro))
    {
        layer->autorelease();
    }
    else
    {
        delete layer;
        layer = NULL;
    }
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init(std::string tag, std::string name, std::string intro)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	//set tags
	picTag = 200;
    sName = name;
    sIntro = intro;

    /////////////////////////////
    // 3. add your codes below...

    //Texture2D *ltex = loadTex("bace.png");

    //    NSString *dirpath = [@SCENEPATH stringByExpandingTildeInPath];
    NSString *docs = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    NSString *dirpath = [docs stringByAppendingPathComponent:@"scenes"];
    
    scenePath = FileUtils::getInstance()->getWritablePath();
    scenePath = scenePath + "scenes/";
    scenePath = scenePath + tag;
    
    texturePath = FileUtils::getInstance()->getWritablePath();
    
    //parse multiple views
    string viewMetaPath = scenePath + "/metaView.txt";
    ssize_t bufferSize = 0;
    unsigned char *buffer = FileUtils::getInstance()->getFileData(viewMetaPath,"r",&bufferSize);
    
    eyeViews = new char*[5];
    viewNames = new char*[5];
    
    char * begin = NULL;
    char * end = NULL;
    begin = (char*)buffer;
    end = strchr(begin,'\r');
    viewNum = 0;
    curViewNum = 0;
    while(true){
        begin = end + 2;
        end = strchr(begin, ',');
        if(!end || viewNum > 4) break;
        *end = 0;
        char *temp = nullptr;
        temp = (char*)malloc(end-begin);
        memcpy(temp,begin+1,end-begin);
        eyeViews[viewNum] = temp;
        begin = end + 1;
        end = strchr(begin, '\r');
        *(end-1) = 0;
        temp = (char*)malloc(end-begin);
        memcpy(temp,begin,end-begin);
        viewNames[viewNum] = temp;
        viewNum++;
    }
    
    scenePath = scenePath + "/" + eyeViews[0];
    
  //  scenePath = [dirpath UTF8String];
  //  scenePath = scenePath + "/";
 
    string path = scenePath+BACEFILE;
    //path = scenePath+"Plane_BLACK.exr";
	Texture2D *ltex = loadTex(path.c_str());
    
    std::string fullpath = scenePath;
    fullpath += "/meta.txt";
    sceneFile = fullpath;
    
    auto sbg = Sprite::create("sceneBG.png");
    sbg->setPosition(cocos2d::Vec2(sbg->getContentSize().width/2,sbg->getContentSize().height/2));
    this->addChild(sbg);
    
    showSprite = Sprite::createWithTexture(ltex);
	showSprite->setPosition(cocos2d::Vec2(showSprite->getContentSize().width/2,showSprite->getContentSize().height/2));
    this->addChild(showSprite, 100);
    
    //renderSprite is for RTT
    renderSprite = new mySprite(-100);
    renderSprite->initWithTex(ltex);
    renderSprite->setPosition(cocos2d::Vec2(showSprite->getContentSize().width/2,showSprite->getContentSize().height/2));
    renderSprite->setTag(picTag);
    renderSprite->autorelease();
    this->addChild(renderSprite, -100);
   
    auto glView = Director::getInstance()->getOpenGLView();
    auto frameSize = glView->getFrameSize();
    float scaleW = frameSize.width/visibleSize.width;
    float scaleH = frameSize.height/visibleSize.height;
    
    spriteX = 0;
    spriteY = 0;
    spriteW = showSprite->getContentSize().width*scaleW;
    spriteH = showSprite->getContentSize().height*scaleH;
    originWidth = showSprite->getContentSize().width;
    originHeight = showSprite->getContentSize().height;
    
	useShader(showSprite);
    useShader(renderSprite);
    
	state = GLProgramState::getOrCreateWithGLProgram(renderSprite->getShaderProgram());
    showState = GLProgramState::getOrCreateWithGLProgram(showSprite->getShaderProgram());
    
    light = new exrTexture;
    light->_imageData = nullptr;
    light->retain();
    light->autorelease();
    objALL = new exrTexture;
    objALL->_imageData = nullptr;
    objALL->retain();
    objALL->autorelease();
    bace = new exrTexture;
    bace->_imageData = nullptr;
    bace->retain();
    bace->autorelease();
    oLight = new exrTexture;
    oLight->_imageData = nullptr;
    oLight->retain();
    oLight->autorelease();
  //  shot = new exrTexture;
 //   shot->_imageData = nullptr;
 //   shot->retain();
 //   shot->autorelease();
    objSingle = new exrTexture;
    objSingle->_imageData = nullptr;
    objSingle->retain();
    objSingle->autorelease();
    
	curLight = nullptr;
	curObj = nullptr;
    
	curOP = nullptr;
    
    sceneCount = 0;
    sceneName = nullptr;
    
 //   oldLight = nullptr;
//    oldObj = nullptr;
//    newLight = nullptr;
 //   newObj = nullptr;
    
    lightUpdated = false;
    loadingView = false;
    
	//load ui json file
//	uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(JSON);
//	this->addChild(uiLayout,100);
//    
//	//set buttons
//	auto b_color = (Button*)Helper::seekWidgetByName(uiLayout, "Button_colorTab");
//    b_color->setPressedActionEnabled(false);
//	b_color->addTouchEventListener(this,toucheventselector(HelloWorld::bColor));
//	auto b_scene = (Button*)Helper::seekWidgetByName(uiLayout,"Button_scene");
//    b_scene->setPressedActionEnabled(false);
//	b_scene->addTouchEventListener(this,toucheventselector(HelloWorld::bScene));
//	auto b_object = (Button*)Helper::seekWidgetByName(uiLayout,"Button_object");
//    b_object->setPressedActionEnabled(false);
//	b_object->addTouchEventListener(this,toucheventselector(HelloWorld::bObject));
//    auto b_objectActive = (Button*)Helper::seekWidgetByName(uiLayout,"Button_object_active");
//    b_objectActive->setPressedActionEnabled(false);
//    b_objectActive->addTouchEventListener(this,toucheventselector(HelloWorld::bObjectActive));
//	auto b_texture = (Button*)Helper::seekWidgetByName(uiLayout,"Button_texTab");
//    b_texture->setPressedActionEnabled(false);
//	b_texture->addTouchEventListener(this,toucheventselector(HelloWorld::bTexture));
//	auto b_view = (Button*)Helper::seekWidgetByName(uiLayout,"Button_view");
//    b_view->setPressedActionEnabled(false);
//	b_view->addTouchEventListener(this,toucheventselector(HelloWorld::bView));
//    auto b_viewActive = (Button*)Helper::seekWidgetByName(uiLayout,"Button_view_active");
//    b_viewActive->setPressedActionEnabled(false);
//    b_viewActive->addTouchEventListener(this,toucheventselector(HelloWorld::bViewActive));
//	auto b_redo = (Button*)Helper::seekWidgetByName(uiLayout,"Button_redo");
//	b_redo->addTouchEventListener(this,toucheventselector(HelloWorld::bRedo));
//	auto b_save = (Button*)Helper::seekWidgetByName(uiLayout,"Button_save");
//	b_save->addTouchEventListener(this,toucheventselector(HelloWorld::bSave));
//	auto b_fullscreen = (Button*)Helper::seekWidgetByName(uiLayout,"Button_fullscreen");
//	b_fullscreen->addTouchEventListener(this,toucheventselector(HelloWorld::bFullScreen));
//    auto b_fullret= (Button*)Helper::seekWidgetByName(uiLayout,"Button_full_ret");
//    b_fullret->addTouchEventListener(this,toucheventselector(HelloWorld::bFullScreenRet));
//    auto b_editDone = (Button*)Helper::seekWidgetByName(uiLayout,"Button_editDone");
//    b_editDone->setPressedActionEnabled(false);
//    b_editDone->addTouchEventListener(this,toucheventselector(HelloWorld::bEditDone));
//    auto b_reset= (Button*)Helper::seekWidgetByName(uiLayout,"Button_reset");
//    b_reset->setPressedActionEnabled(false);
//    b_reset->addTouchEventListener(this,toucheventselector(HelloWorld::bReset));
//    
//    b_fullret->setEnabled(false);
//    Helper::seekWidgetByName(uiLayout, "Panel_button")->setEnabled(false);
//    
//   // auto s_texture = (ui::ScrollView*)Helper::seekWidgetByName(uiLayout,"Scroll_Texture");
//  //  s_texture->setBounceEnabled(true);
//    
////	views[0] = "Panel_Object";
////	views[1] = "Panel_color";
////	views[2] = "Scroll_Texture";
//	curView = 0;
////	panels[0] = Helper::seekWidgetByName(uiLayout, "Panel_Object");
////	panels[1] = Helper::seekWidgetByName(uiLayout, "Panel_color");
////	panels[2] = Helper::seekWidgetByName(uiLayout, "Scroll_Texture");
//  //  panels[3] = Helper::seekWidgetByName(uiLayout, "Scroll_view");
//    
//  //  panels[0]->setVisible(true);
//  //  for(int i=1;i<4;i++)
//  //      panels[i]->setVisible(false);
//    
//    objectList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_object");
//    objectList->setPosition(cocos2d::Vec2(512,15));
//    objectList->setAnchorPoint(cocos2d::Vec2(0.5,0));
//
//	sR = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_red");
//    sR->setVisible(false);
//	sG = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_green");
//    sG->setVisible(false);
//	sB = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_blue");
//    sB->setVisible(false);
//    sL = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_light");
//    sL->setVisible(false);
//    
//    csL = ControlSlider::create("icon/main-slider-400-light-0.png", "icon/main-slider-400-light-0.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
//    csL->setMaximumValue(2);
//    csL->setMinimumValue(0);
//    csL->setScale(0.8,1.0);
//    csL->setPosition(sL->getPosition());
//    csL->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderL), Control::EventType::VALUE_CHANGED);
//    csL->setCascadeOpacityEnabled(true);
//    (sL->getParent())->addChild(csL,200);
//  //  panels[0]->addChild(csL);
//    
//    csR = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
//    csR->setContentSize(sR->getContentSize());
//    csR->setMaximumValue(1);
//    csR->setMinimumValue(0);
//    csR->setPositionX(sR->getPositionX());
//    csR->setPositionY(sR->getPositionY()-5);
//    csR->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderR), Control::EventType::VALUE_CHANGED);
//    csR->setCascadeOpacityEnabled(true);
//    (sR->getParent())->addChild(csR,200);
// //   panels[1]->addChild(csR);
//    
//    csG = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
//    csG->setMaximumValue(1);
//    csG->setMinimumValue(0);
//    csG->setPositionX(sG->getPositionX());
//    csG->setPositionY(sG->getPositionY());
//    csG->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderG), Control::EventType::VALUE_CHANGED);
//    csG->setCascadeOpacityEnabled(true);
//    (sG->getParent())->addChild(csG,200);
// //   panels[1]->addChild(csG);
//    
//    csB = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
//    csB->setMaximumValue(1);
//    csB->setMinimumValue(0);
//    csB->setPositionX(sB->getPositionX());
//    csB->setPositionY(sB->getPositionY());
//    csB->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderB), Control::EventType::VALUE_CHANGED);
//    csB->setCascadeOpacityEnabled(true);
//    (sB->getParent())->addChild(csB,200);
// //   panels[1]->addChild(csB);
//    
//  //  csR->setVisible(false);
// //   csG->setVisible(false);
// //   csB->setVisible(false);
//    
//    Texture2D *maskShow = Director::getInstance()->getTextureCache()->addImage("icon/main-colorsample-0.png");
//	i_color = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_colorSample");
//	Sprite *imageSprite = (Sprite*)i_color->getVirtualRenderer();
//	userShaderRGB(imageSprite);
//	stateColor = GLProgramState::getOrCreateWithGLProgram(imageSprite->getShaderProgram());
//	stateColor->setUniformInt("num",3);
//    stateColor->setUniformTexture("u_mask", maskShow);
//    ImageView* i_sR = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_red");
//    Sprite *si_sR = (Sprite*)i_sR->getVirtualRenderer();
//    userShaderRGB(si_sR);
//    stateR = GLProgramState::getOrCreateWithGLProgram(si_sR->getShaderProgram());
//    stateR->setUniformInt("num", 0);
//    stateR->setUniformTexture("u_mask", si_sR->getTexture());
//    ImageView* i_sG = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_green");
//    Sprite *si_sG = (Sprite*)i_sG->getVirtualRenderer();
//    userShaderRGB(si_sG);
//    stateG = GLProgramState::getOrCreateWithGLProgram(si_sG->getShaderProgram());
//    stateG->setUniformInt("num", 1);
//    stateG->setUniformTexture("u_mask", si_sG->getTexture());
//    ImageView* i_sB = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_blue");
//    Sprite *si_sB = (Sprite*)i_sB->getVirtualRenderer();
//    userShaderRGB(si_sB);
//    stateB = GLProgramState::getOrCreateWithGLProgram(si_sB->getShaderProgram());
//    stateB->setUniformInt("num", 2);
//    stateB->setUniformTexture("u_mask", si_sB->getTexture());

    Texture2D *loadTex = Director::getInstance()->getTextureCache()->addImage("load.png");
    loadSprite = Sprite::createWithTexture(loadTex);
    loadSprite->setPosition(cocos2d::Vec2(loadSprite->getContentSize().width/2,loadSprite->getContentSize().height/2));
    this->addChild(loadSprite,150);
    
    loadPro = ProgressTimer::create(Sprite::create("progress-bar.png"));
    loadPro->setType(ProgressTimer::Type::BAR);
    loadPro->setPosition(cocos2d::Vec2(500,350));
    loadPro->setBarChangeRate(cocos2d::Vec2(1,0));
    loadPro->setMidpoint(cocos2d::Vec2(0,0.5));
    this->addChild(loadPro,200);
    
    proBG = Sprite::create("progress-frame.png");
    proBG->setPosition(cocos2d::Vec2(500,350));
    this->addChild(proBG,150);
    
  //  getTexFileName(sceneFile.c_str());
    
//    viewList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_view");
//    texList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_Texture");
//    
//    viewList->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
//    viewList->cocos2d::Node::setPosition(512, 100);
//    texList->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
//    texList->cocos2d::Node::setPosition(552,64);
//    
//    cocos2d::ui::Text *label_sname = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_scene");
//    float textW = label_sname->getContentSize().width;
//    label_sname->setString(name);
//    textW = label_sname->getContentSize().width - textW;
//    cocos2d::ui::Widget *sceneImg = Helper::seekWidgetByName(uiLayout, "Image_name");
//  //  sceneImg->setContentSize(cocos2d::Size(sceneImg->getContentSize().width+textW,sceneImg->getContentSize().height));
//    cocos2d::ui::Widget *sep = Helper::seekWidgetByName(uiLayout, "Image_sep");
//    sep->setPositionX(sep->getPositionX()+textW);
//    cocos2d::ui::Text *label_view = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_view");
//    label_view->setPositionX(label_view->getPositionX()+textW);
// //   float textW2 = label_view->getContentSize().width;
// //   label_view->setString(eyeViews[curViewNum]);
// //   textW2 = label_view->getContentSize().width-textW2;
////    textW += textW2;
//    sceneImg->setContentSize(cocos2d::Size(sceneImg->getContentSize().width+textW,sceneImg->getContentSize().height));
//    auto bSceneInfo = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title");
//    bSceneInfo->setPositionX(bSceneInfo->getPositionX()+textW);
//    bSceneInfo->addTouchEventListener(this,toucheventselector(HelloWorld::bSceneInfo));
//    auto bSceneInfoUp = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title_up");
//    bSceneInfoUp->setPositionX(bSceneInfo->getPositionX());
//    bSceneInfoUp->addTouchEventListener(this,toucheventselector(HelloWorld::bSceneInfo));
//    sceneImg->setVisible(false);
//    
//    cocos2d::ui::Text *slabel = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_discrib");
//    sceneDis = Label::create();
//    sceneDis->setAnchorPoint(slabel->getAnchorPoint());
//    sceneDis->setSystemFontName(slabel->getFontName());
//    sceneDis->setSystemFontSize(slabel->getFontSize());
//    sceneDis->setWidth(slabel->getContentSize().width);
//    sceneDis->setLineBreakWithoutSpace(true);
//    string disText = "描述：\n"+intro;
//    for(int i=0;i<30;i++)
//        disText += "111";
//    sceneDis->setString(disText);
//    
//    auto sstext = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "ScrollView_stext");
//    sstext->setAnchorPoint(cocos2d::Vec2(0,1));
//    sstext->addChild(sceneDis);
//    
//    sstext->setPositionY(165);
//    float height = sceneDis->getContentSize().height;
//    if(height < 150)
//        sstext->setContentSize(cocos2d::Size(360,height));
//    sstext->setInnerContainerSize(cocos2d::Size(360,height));
//    sceneDis->setPosition(cocos2d::Size(0,height));
    
  //  choose = Label::create("", "华文仿宋", 24);
  //  choose->setPosition(cocos2d::Vec2(500,300));
  //  this->addChild(choose,500);
    
    swallow = SwallowLayer::create();
    swallow->setContentSize(cocos2d::Size(1024,768));
    this->addChild(swallow,1000);
    
    viewChanged = true;
    retPressed = false;
    playingAni = false;
    
    return true;
}

void HelloWorld::bSceneInfo(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    static float originW = 0;
    cocos2d::ui::Widget *sceneImg = Helper::seekWidgetByName(uiLayout, "Image_name");
    float offy = 225-48;
    
    bool up = false;
    if(sceneImg->getContentSize().height == 225)
        up = true;
    else
        originW = sceneImg->getContentSize().width;
    
    if(up){
        sceneImg->setContentSize(cocos2d::Size(originW,48));
        offy = -offy;
        Helper::seekWidgetByName(uiLayout, "Button_title")->setVisible(true);
        Helper::seekWidgetByName(uiLayout, "Button_title_up")->setVisible(false);
        Helper::seekWidgetByName(uiLayout, "ScrollView_stext")->setVisible(false);
    }
    else{
        sceneImg->setContentSize(cocos2d::Size(400,225));
        Helper::seekWidgetByName(uiLayout, "Button_title")->setVisible(false);
        Helper::seekWidgetByName(uiLayout, "Button_title_up")->setVisible(true);
        Helper::seekWidgetByName(uiLayout, "ScrollView_stext")->setVisible(true);
    }
    Vector<Node*> temp = sceneImg->getChildren();
    for(int i=0;i<temp.size();i++){
        if(temp.at(i)->getName()!="ScrollView_stext")
            temp.at(i)->setPositionY(temp.at(i)->getPositionY()+offy);
    }
  //  ((Node*)sender)->setVisible(false);
}

void HelloWorld::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();

    uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(JSON);
    this->addChild(uiLayout,100);
    
    //set buttons
    auto b_color = (Button*)Helper::seekWidgetByName(uiLayout, "Button_colorTab");
    b_color->setPressedActionEnabled(false);
    b_color->addTouchEventListener(this,toucheventselector(HelloWorld::bColor));
    auto b_scene = (Button*)Helper::seekWidgetByName(uiLayout,"Button_scene");
    b_scene->setPressedActionEnabled(false);
    b_scene->addTouchEventListener(this,toucheventselector(HelloWorld::bScene));
    auto b_object = (Button*)Helper::seekWidgetByName(uiLayout,"Button_object");
    b_object->setPressedActionEnabled(false);
    b_object->addTouchEventListener(this,toucheventselector(HelloWorld::bObject));
    auto b_objectActive = (Button*)Helper::seekWidgetByName(uiLayout,"Button_object_active");
    b_objectActive->setPressedActionEnabled(false);
    b_objectActive->addTouchEventListener(this,toucheventselector(HelloWorld::bObjectActive));
    auto b_texture = (Button*)Helper::seekWidgetByName(uiLayout,"Button_texTab");
    b_texture->setPressedActionEnabled(false);
    b_texture->addTouchEventListener(this,toucheventselector(HelloWorld::bTexture));
    auto b_light = (Button*)Helper::seekWidgetByName(uiLayout,"Button_lightTab");
    b_light->setPressedActionEnabled(false);
    b_light->addTouchEventListener(this,toucheventselector(HelloWorld::bLight));
    auto b_view = (Button*)Helper::seekWidgetByName(uiLayout,"Button_view");
    b_view->setPressedActionEnabled(false);
    b_view->addTouchEventListener(this,toucheventselector(HelloWorld::bView));
    auto b_viewActive = (Button*)Helper::seekWidgetByName(uiLayout,"Button_view_active");
    b_viewActive->setPressedActionEnabled(false);
    b_viewActive->addTouchEventListener(this,toucheventselector(HelloWorld::bViewActive));
    auto b_redo = (Button*)Helper::seekWidgetByName(uiLayout,"Button_redo");
    b_redo->addTouchEventListener(this,toucheventselector(HelloWorld::bRedo));
    auto b_save = (Button*)Helper::seekWidgetByName(uiLayout,"Button_save");
    b_save->addTouchEventListener(this,toucheventselector(HelloWorld::bSave));
    auto b_fullscreen = (Button*)Helper::seekWidgetByName(uiLayout,"Button_fullscreen");
    b_fullscreen->addTouchEventListener(this,toucheventselector(HelloWorld::bFullScreen));
    auto b_fullret= (Button*)Helper::seekWidgetByName(uiLayout,"Button_full_ret");
    b_fullret->addTouchEventListener(this,toucheventselector(HelloWorld::bFullScreenRet));
    auto b_editDone = (Button*)Helper::seekWidgetByName(uiLayout,"Button_editDone");
    b_editDone->setPressedActionEnabled(false);
    b_editDone->addTouchEventListener(this,toucheventselector(HelloWorld::bEditDone));
    auto b_reset= (Button*)Helper::seekWidgetByName(uiLayout,"Button_reset");
    b_reset->setPressedActionEnabled(false);
    b_reset->addTouchEventListener(this,toucheventselector(HelloWorld::bReset));
    
    b_fullret->setEnabled(false);
    Helper::seekWidgetByName(uiLayout, "Panel_button")->setEnabled(false);
    
    // auto s_texture = (ui::ScrollView*)Helper::seekWidgetByName(uiLayout,"Scroll_Texture");
    //  s_texture->setBounceEnabled(true);
    
    //	views[0] = "Panel_Object";
    //	views[1] = "Panel_color";
    //	views[2] = "Scroll_Texture";
    curView = 0;
    //	panels[0] = Helper::seekWidgetByName(uiLayout, "Panel_Object");
    //	panels[1] = Helper::seekWidgetByName(uiLayout, "Panel_color");
    //	panels[2] = Helper::seekWidgetByName(uiLayout, "Scroll_Texture");
    //  panels[3] = Helper::seekWidgetByName(uiLayout, "Scroll_view");
    
    //  panels[0]->setVisible(true);
    //  for(int i=1;i<4;i++)
    //      panels[i]->setVisible(false);
    
    objectList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_object");
    objectList->setPosition(cocos2d::Vec2(512,15));
    objectList->setAnchorPoint(cocos2d::Vec2(0.5,0));
    
    sR = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_red");
    sR->setVisible(false);
    sG = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_green");
    sG->setVisible(false);
    sB = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_blue");
    sB->setVisible(false);
    sL = (Slider*)Helper::seekWidgetByName(uiLayout, "Slider_light");
    sL->setVisible(false);
    
    csL = ControlSlider::create("icon/main-slider-400-light-0.png", "icon/main-slider-400-light-0.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
    csL->setMaximumValue(2);
    csL->setMinimumValue(0);
    csL->setContentSize(sL->getContentSize());
    csL->setPositionX(sL->getPositionX());
    csL->setPositionY(sL->getPositionY()-5);
    csL->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderL), Control::EventType::VALUE_CHANGED);
    csL->setCascadeOpacityEnabled(true);
    (sL->getParent())->addChild(csL,200);
    //  panels[0]->addChild(csL);
    
    csR = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
    csR->setContentSize(sR->getContentSize());
    csR->setMaximumValue(1);
    csR->setMinimumValue(0);
    csR->setPositionX(sR->getPositionX());
    csR->setPositionY(sR->getPositionY()-5);
    csR->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderR), Control::EventType::VALUE_CHANGED);
    csR->setCascadeOpacityEnabled(true);
    (sR->getParent())->addChild(csR,200);
    //   panels[1]->addChild(csR);
    
    csG = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
    csG->setMaximumValue(1);
    csG->setMinimumValue(0);
    csG->setPositionX(sG->getPositionX());
    csG->setPositionY(sG->getPositionY());
    csG->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderG), Control::EventType::VALUE_CHANGED);
    csG->setCascadeOpacityEnabled(true);
    (sG->getParent())->addChild(csG,200);
    //   panels[1]->addChild(csG);
    
    csB = ControlSlider::create("assets/sliderbg.png", "assets/sliderbg.png", "icon/main-slider-bt-normal.png", "icon/main-slider-bt-pressed.png");
    csB->setMaximumValue(1);
    csB->setMinimumValue(0);
    csB->setPositionX(sB->getPositionX());
    csB->setPositionY(sB->getPositionY());
    csB->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderB), Control::EventType::VALUE_CHANGED);
    csB->setCascadeOpacityEnabled(true);
    (sB->getParent())->addChild(csB,200);
    //   panels[1]->addChild(csB);
    
    //  csR->setVisible(false);
    //   csG->setVisible(false);
    //   csB->setVisible(false);
    
    Texture2D *maskShow = Director::getInstance()->getTextureCache()->addImage("icon/main-colorsample-0.png");
    i_color = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_colorSample");
    Sprite *imageSprite = (Sprite*)i_color->getVirtualRenderer();
    userShaderRGB(imageSprite);
    stateColor = GLProgramState::getOrCreateWithGLProgram(imageSprite->getShaderProgram());
    stateColor->setUniformInt("num",3);
    stateColor->setUniformTexture("u_mask", maskShow);
    ImageView* i_sR = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_red");
    Sprite *si_sR = (Sprite*)i_sR->getVirtualRenderer();
    userShaderRGB(si_sR);
    stateR = GLProgramState::getOrCreateWithGLProgram(si_sR->getShaderProgram());
    stateR->setUniformInt("num", 0);
    stateR->setUniformTexture("u_mask", si_sR->getTexture());
    ImageView* i_sG = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_green");
    Sprite *si_sG = (Sprite*)i_sG->getVirtualRenderer();
    userShaderRGB(si_sG);
    stateG = GLProgramState::getOrCreateWithGLProgram(si_sG->getShaderProgram());
    stateG->setUniformInt("num", 1);
    stateG->setUniformTexture("u_mask", si_sG->getTexture());
    ImageView* i_sB = (ImageView*)Helper::seekWidgetByName(uiLayout, "Image_blue");
    Sprite *si_sB = (Sprite*)i_sB->getVirtualRenderer();
    userShaderRGB(si_sB);
    stateB = GLProgramState::getOrCreateWithGLProgram(si_sB->getShaderProgram());
    stateB->setUniformInt("num", 2);
    stateB->setUniformTexture("u_mask", si_sB->getTexture());
    
    viewList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_view");
    texList = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "Scroll_Texture");
    
    viewList->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    viewList->cocos2d::Node::setPosition(512, 100);
    texList->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    texList->cocos2d::Node::setPosition(552,64);
    
    cocos2d::ui::Text *label_sname = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_scene");
    float textW = label_sname->getContentSize().width;
    label_sname->setString(sName);
    textW = label_sname->getContentSize().width - textW;
    cocos2d::ui::Widget *sceneImg = Helper::seekWidgetByName(uiLayout, "Image_name");
    //  sceneImg->setContentSize(cocos2d::Size(sceneImg->getContentSize().width+textW,sceneImg->getContentSize().height));
    cocos2d::ui::Widget *sep = Helper::seekWidgetByName(uiLayout, "Image_sep");
    sep->setPositionX(sep->getPositionX()+textW);
    cocos2d::ui::Text *label_view = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_view");
    label_view->setPositionX(label_view->getPositionX()+textW);
    //   float textW2 = label_view->getContentSize().width;
    //   label_view->setString(eyeViews[curViewNum]);
    //   textW2 = label_view->getContentSize().width-textW2;
    //    textW += textW2;
    sceneImg->setContentSize(cocos2d::Size(sceneImg->getContentSize().width+textW,sceneImg->getContentSize().height));
    auto bSceneInfo = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title");
    bSceneInfo->setPositionX(bSceneInfo->getPositionX()+textW);
    bSceneInfo->addTouchEventListener(this,toucheventselector(HelloWorld::bSceneInfo));
    auto bSceneInfoUp = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title_up");
    bSceneInfoUp->setPositionX(bSceneInfo->getPositionX());
    bSceneInfoUp->addTouchEventListener(this,toucheventselector(HelloWorld::bSceneInfo));
    sceneImg->setVisible(false);
    
    cocos2d::ui::Text *slabel = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_discrib");
    sceneDis = Label::create();
    sceneDis->setAnchorPoint(slabel->getAnchorPoint());
    sceneDis->setSystemFontName(slabel->getFontName());
    sceneDis->setSystemFontSize(slabel->getFontSize());
    sceneDis->setWidth(slabel->getContentSize().width);
    sceneDis->setLineBreakWithoutSpace(true);
    string disText = "描述：\n"+sIntro;
//    for(int i=0;i<30;i++)
//        disText += "111";
    sceneDis->setString(disText);
    
    auto sstext = (cocos2d::ui::ScrollView*)Helper::seekWidgetByName(uiLayout, "ScrollView_stext");
    sstext->setAnchorPoint(cocos2d::Vec2(0,1));
    sstext->addChild(sceneDis);
    
    sstext->setPositionY(165);
    float height = sceneDis->getContentSize().height;
    if(height < 150)
        sstext->setContentSize(cocos2d::Size(360,height));
    sstext->setInnerContainerSize(cocos2d::Size(360,height));
    sceneDis->setPosition(cocos2d::Size(0,height));
    
    //animations
    ani_ret = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_return");
    
    loadView(0);
}

void HelloWorld::viewItem(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType event){
    if (event != Widget::TouchEventType::ENDED) {
        return;
    }
    
    if(loadingView)
        return;
    
    loadingView = true;
    
    Widget *w = (Widget*)pSender;
    int num = w->getTag();
    
    loadView(num);
    
    viewChanged = true;
    
    ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_btn3_in");
    ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_viewPanel_out");
}

void HelloWorld::loadView(int num){
    for(int i=0;i<objCount;i++){
        if(objects[i]->objBace){
            objects[i]->objBace->release();
            if(objects[i]->objBace->_imageData)
                free(objects[i]->objBace->_imageData);
        }
        if(objects[i]->UV){
            objects[i]->UV->release();
            if(objects[i]->UV->_imageData)
                free(objects[i]->UV->_imageData);
        }
        free(objects[i]);
    }
    if(objects)
        delete objects;
    
    for(int i=0;i<lightCount;i++){
        if (lights[i]->bace) {
            free(lights[i]->bace);
            lights[i]->baceTex->release();
        }
        free(lights[i]);
    }
    if(lights)
        delete lights;
    
    if (light->_imageData)
        free(light->_imageData);
    if(objALL->_imageData)
        free(objALL->_imageData);
    if(objSingle->_imageData)
        free(objSingle->_imageData);
    
    curViewNum = num;
    curObj = NULL;
    curLight = NULL;
    
    int end = scenePath.rfind('/');
    string dirPath = scenePath.substr(0,end+1);
    
    scenePath = dirPath+eyeViews[num];
    
    sceneFile = scenePath+"/meta.txt";
    
    getTexFileName(sceneFile.c_str());
    
    // create view list
    viewList->removeAllChildren();
    for(int i=0,j=0;i<viewNum;i++){
        if(i == curViewNum)
            continue;
        
        auto viewLabel = Label::create();
        viewLabel->setPositionX(10+220*j+100);
        viewLabel->setAnchorPoint(cocos2d::Vec2(0.5,0));
        viewLabel->setPositionY(0);
        viewLabel->setSystemFontName("华文仿宋");
        viewLabel->setColor(Color3B::BLACK);
        viewLabel->setSystemFontSize(16);
        viewLabel->setString(viewNames[i]);
        auto shadow = Sprite::create("icon/main-view-thumb-bg.png");
        shadow->setAnchorPoint(cocos2d::Vec2(0.5,0));
        shadow->setPosition(10+220*j+100, 12);
        
        string thumb = dirPath+eyeViews[i];
        thumb += "/thumb.png";
        Texture2D *t = Director::getInstance()->getTextureCache()->addImage(thumb);
        
        Button* btn = Button::create();
        btn->setScale9Enabled(true);
        btn->loadTextureNormal(thumb);
        btn->setCapInsets(cocos2d::Rect(0,0,t->getContentSize().width,t->getContentSize().height));
        btn->setTag(i);
        btn->setSize(cocos2d::Size(192,144));
        btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::viewItem, this));
        btn->setAnchorPoint(cocos2d::Vec2(0.5,0));
        btn->setPositionX(10+220*j+100);
        btn->setPositionY(20);
        Layout *custom_item = Layout::create();
        custom_item->setSize(btn->getContentSize());
        custom_item->addChild(shadow);
        custom_item->addChild(btn);
        custom_item->addChild(viewLabel);
        viewList->addChild(custom_item);
        custom_item->setCascadeOpacityEnabled(true);
        j++;
    }
    float width = 220*(viewNum-1);
    if(width < 1024)
        viewList->setContentSize(cocos2d::Size(width,170));
    viewList->setInnerContainerSize(cocos2d::Size(width,170));
    
    // create objects list
    objectList->removeAllChildren();
    int c = objCount+lightCount;
    for(int i=0;i<c;i++){
        char *name;
        if(i < objCount)
            name = objects[i]->objName;
        else
            name = lights[i-objCount]->lightName;
        
        Button* custom_button = Button::create();
        custom_button->setScale9Enabled(true);
        custom_button->setSize(cocos2d::Size(120, 90));
        custom_button->loadTextures("icon/main-edit-comp-normal.png", "icon/main-edit-comp-normal.png");
        custom_button->setTitleColor(Color3B::BLACK);
    
        custom_button->setTag(i);
        custom_button->setAnchorPoint(cocos2d::Vec2(0,0));
        custom_button->setTitleText(name);
        custom_button->setTitleFontName("华文仿宋");
        custom_button->setTitleFontSize(20);
        custom_button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::objectItem, this));
        
        Layout *custom_item = Layout::create();
        custom_item->setSize(custom_button->getContentSize());
        custom_item->setTag(i);
        custom_button->setPosition(cocos2d::Vec2(7+134*i,0));
        custom_item->addChild(custom_button);
        
        objectList->addChild(custom_item);
        custom_item->setCascadeOpacityEnabled(true);
    }
    width = 134*c;
    if(width < 1024)
        objectList->setContentSize(cocos2d::Size(width,90));
    objectList->setInnerContainerSize(cocos2d::Size(width,90));
    
    // create texture list
    texList->removeAllChildren();
    string path = texturePath + "Texture_button/";
    NSFileManager *tempFM = [NSFileManager defaultManager];
    NSDirectoryEnumerator *direnum = [tempFM enumeratorAtPath:[NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding]];
    NSMutableArray *files = [NSMutableArray arrayWithCapacity:5];
    NSString *filename;
    while(filename = [direnum nextObject]){
        if ([[filename pathExtension] isEqualToString:@"png"]) {
            [files addObject:filename];
        }
    }
    
    NSEnumerator *fileenum = [files objectEnumerator];
    
    int i=0;
    while (filename = [fileenum nextObject]) {
        const char *name = [filename UTF8String];
        string texPath = path + name;
        Button *btn = Button::create();
        btn->setScale9Enabled(true);
        btn->loadTextureNormal(texPath);
        btn->setSize(cocos2d::Size(100,100));
        btn->setTitleText(name);
        btn->setTitleFontSize(0);
        btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::texItem, this));
        Layout *custom_item = Layout::create();
        custom_item->setSize(btn->getContentSize());
        btn->setPosition(cocos2d::Vec2(60+110*i,50));
        custom_item->addChild(btn);
        
        texList->addChild(custom_item);
        custom_item->setCascadeOpacityEnabled(true);
        i++;
    }
   // texList->setInnerContainerSize(cocos2d::Size(200+i*100,120));
    width = 110*i;
    if(width < 920)
        texList->setContentSize(cocos2d::Size(width,100));
    else
        texList->setContentSize(cocos2d::Size(920,100));
    texList->setInnerContainerSize(cocos2d::Size(width,100));
    
    proBG->setVisible(true);
    loadPro->setVisible(true);
  //  csL->setVisible(true);
    loadPro->setPercentage(0);
    renderSprite->setVisible(true);
    
 //   this->addChild(swallow,100);
    swallow->swallow();
    curView = 0;
    
    cocos2d::ui::Text *label_view = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout,"Label_view");
    float textW = label_view->getContentSize().width;
    label_view->setString(viewNames[curViewNum]);
    textW = label_view->getContentSize().width-textW;
    auto sceneImg = Helper::seekWidgetByName(uiLayout, "Image_name");
    sceneImg->setContentSize(cocos2d::Size(sceneImg->getContentSize().width+textW,sceneImg->getContentSize().height));
    auto bSceneInfo = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title");
    bSceneInfo->setPositionX(bSceneInfo->getPositionX()+textW);
    auto bSceneInfoUp = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title_up");
    bSceneInfoUp->setPositionX(bSceneInfo->getPositionX());
    auto bSceneInfo2 = (Button*)Helper::seekWidgetByName(uiLayout, "Button_title2");
    bSceneInfo2->setContentSize(sceneImg->getContentSize());
    bSceneInfo2->addTouchEventListener(this,toucheventselector(HelloWorld::bSceneInfo));
    
    if(objCount)
        setCurObj(0);
    else
        setCurLight(0);
    
    initTexture();
    
    OPInfo *temp;
    OPInfo *temp1 = curOP;
    curOP = curOP->next;
    
    for(int i=0;i<20;i++){
        temp = new OPInfo;
        temp->type = EMPTY;
        temp->next = curOP;
        curOP = temp;
    }
    
    temp1->next = curOP;
    curOP = temp1;
    
    setAlphaAll(255);
    
    this->scheduleUpdate();
    
    loadingView = false;
}

void HelloWorld::setAlphaAll(GLubyte value){
    uiLayout->setOpacity(value);
    float a = value/255.0;
    stateColor->setUniformFloat("alpha", a);
    stateR->setUniformFloat("alpha", a);
    stateG->setUniformFloat("alpha", a);
    stateB->setUniformFloat("alpha", a);
}

void HelloWorld::texItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event){
    if (event != Widget::TouchEventType::ENDED) {
        return;
    }
    
    if(!curObj)
        return;
    
    swallow->swallow();
    
    Button *btn = (Button*)pSender;
    string name = btn->getTitleText();

    curObj->tex = loadUserTex(name.c_str());
    curObj->texName = name;
    
    showState->setUniformTexture(TEX, curObj->tex);
    if(lightCount>0)
        showState->setUniformInt(STATE, 1);
    else
        showState->setUniformInt(STATE, -1);
    
    swallow->remove();
}

//callbacks for RGB slider
void HelloWorld::sliderR(Ref *sender,Control::EventType type){
	auto slider = (ControlSlider*)sender;
	if(curObj){
        
		curObj->rgb[0] = slider->getValue();
		showState->setUniformVec4(COLOR,cocos2d::Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
			curLight->rgb[0] = slider->getValue();
			showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderG(Ref *sender,Control::EventType type){
	auto slider = (ControlSlider*)sender;
	if(curObj){
		curObj->rgb[1] = slider->getValue();
		showState->setUniformVec4(COLOR,cocos2d::Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
			curLight->rgb[1] = slider->getValue();
			showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderB(Ref *sender,Control::EventType event){
	auto slider = (ControlSlider*)sender;
	if(curObj){
		curObj->rgb[2] = slider->getValue();
		showState->setUniformVec4(COLOR,cocos2d::Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
			curLight->rgb[2] = slider->getValue();
			showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderL(Ref *sender,Control::EventType event){
	auto slider = (ControlSlider*)sender;
	if(curObj){
		return;
	}
	else{
		if(curLight){
			curLight->intensity = slider->getValue();
			showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
		}
	}
}


//read contentfile and get objects and lights, their names are stored in objFiles and lightFiles
bool HelloWorld::getTexFileName(const char* contentfile){
	if(!contentfile)
		return false;
    
	//read .txt file
	unsigned char *buffer = NULL;
	ssize_t bufferSize = 0;
    
	buffer = FileUtils::getInstance()->getFileData(contentfile,"r",&bufferSize);

	if(buffer == NULL)
		return false;
    
	//parse the file content
	char * begin = NULL;
	char * end = NULL;
    
	//get dir path
	begin = (char*)contentfile;
	end = strrchr(begin,'/');
	int length = end-begin+1;
	filepath = (char*)malloc(length+1);
	memcpy(filepath,begin,length);
	*(filepath+length) = 0;
    
	//read bace texture
	//bace = loadTex(getFilePath("bace.exr"));
    
	//get object count
	begin = (char*)buffer;
	end = strchr(begin,'\r');
	*end = 0;
	objCount = atoi(begin);
    
	if(objCount > 0)
		objects = new objInfo*[objCount];
    
	//get object info
	for(int i=0;i<objCount;i++){
		//malloc memory
		objects[i] = (objInfo*)malloc(sizeof(objInfo));
		memset(objects[i],0,sizeof(objInfo));
        
		//object name
		begin = end+2;
		end = strchr(begin,'\r');
		*(end-1) = 0;
		objects[i]->objName = (char*)malloc(end-begin-1);
   //     CCLog("input: %s",begin);
		memcpy(objects[i]->objName,begin+1,end-begin-1);
        
		//object bace file
		begin = end+2;
		end = strchr(begin,'\r');
		*(end-1) = 0;
		objects[i]->baceFile = (char*)malloc(end-begin-1);
		memcpy(objects[i]->baceFile,begin+1,end-begin-1);
        
		//object uv file
		begin = end+2;
		end = strchr(begin,'\r');
		*(end-1) = 0;
		objects[i]->uvFile = (char*)malloc(end-begin-1);
		memcpy(objects[i]->uvFile,begin+1,end-begin-1);
        
		//object diffuse color
		begin = strchr(end+2,' ')+1;
		end = strchr(begin,' ');
		*end = 0;
		objects[i]->tempRGB[0] = atoi(begin)/255.0;
        objects[i]->originRGB[0] = objects[i]->tempRGB[0];
		objects[i]->rgb[0] = 1.0;
		begin = end+1;
		end = strchr(begin,' ');
		*end = 0;
		objects[i]->tempRGB[1] = atoi(begin)/255.0;
        objects[i]->originRGB[1] = objects[i]->tempRGB[1];
		objects[i]->rgb[1] = 1.0;
		begin = end+1;
		end = strchr(begin,')');
		*end = 0;
		objects[i]->tempRGB[2] = atoi(begin)/255.0;
        objects[i]->originRGB[2] = objects[i]->tempRGB[2];
		objects[i]->rgb[2] = 1.0;
        
		end = end+1;
        
        //object texture
		begin = end+2;
		end = strchr(begin,'\r');
		*end = 0;
		if(strcmp(begin,"0")){
			objects[i]->tex = loadUserTex(begin);
            objects[i]->texName = begin;
      //      objects[i]->originTex = objects[i]->tex;
		}
        else
            objects[i]->texName = "";
        objects[i]->originTexName = objects[i]->texName;
	}
    
	//get light count
	begin = end+2;
	end = strchr(begin,'\r');
	*end = 0;
	lightCount = atoi(begin);
    
	if(lightCount > 0)
		lights = new lightInfo*[lightCount];
    else{
		lights = new lightInfo*[1];
		lights[0] = (lightInfo*)malloc(sizeof(lightInfo));
		memset(lights[0],0,sizeof(lightInfo));
		lights[0]->lightFile = BACEFILE;
		lights[0]->intensity = 1.0;
		lights[0]->rgb[0] = 1.0;
		lights[0]->rgb[1] = 1.0;
		lights[0]->rgb[2] = 1.0;
	}
    
	//get light info
	for(int i=0;i<lightCount;i++){
		//malloc memory
		lights[i] = (lightInfo*)malloc(sizeof(lightInfo));
		memset(lights[i],0,sizeof(lightInfo));
        
		//light name
		begin = end+2;
		end = strchr(begin,'\r');
		*(end-1) = 0;
		lights[i]->lightName = (char*)malloc(end-begin-1);
		memcpy(lights[i]->lightName,begin+1,end-begin-1);
        
		//light file
		begin = end+2;
		end = strchr(begin,'\r');
		*(end-1) = 0;
		lights[i]->lightFile = (char*)malloc(end-begin-1);
		memcpy(lights[i]->lightFile,begin+1,end-begin-1);
        
		begin = strchr(end+2,' ')+1;
		end = strchr(begin,' ');
		*end = 0;
		lights[i]->rgb[0] = atoi(begin)/255.0;
        lights[i]->originRGB[0] = lights[i]->rgb[0];
		//objects[i]->rgb[0] = 1.0;
		begin = end+1;
		end = strchr(begin,' ');
		*end = 0;
		lights[i]->rgb[1] = atoi(begin)/255.0;
        lights[i]->originRGB[1] = lights[i]->rgb[1];
		//objects[i]->rgb[1] = 1.0;
		begin = end+1;
		end = strchr(begin,')');
		*end = 0;
		lights[i]->rgb[2] = atoi(begin)/255.0;
        lights[i]->originRGB[2] = lights[i]->rgb[2];
		//objects[i]->rgb[2] = 1.0;
        
		begin = end+3;
		end = strchr(begin,'\r');
		*end = 0;
		lights[i]->intensity = atoi(begin)/100.0;
        lights[i]->originIntensity = lights[i]->intensity;
	}
    
	free(buffer);
    
	return true;
}

char *HelloWorld::getFilePath(const char *filename){
	char *temp = (char*)malloc(strlen(filepath)+strlen(filename)+1);
	memcpy(temp,filepath,strlen(filepath));
	memcpy(temp+strlen(filepath),filename,strlen(filename)+1);
	return temp;
}

//init, gen all needed texture
bool HelloWorld::initTexture(){
    
    totalProcess = 0;
    
	OPInfo *temp = NULL;
    
	//init object
	if(objCount > 0){
		for(int i=0;i<objCount;i++){
			temp = new OPInfo;
			temp->type = ADDOBJ;
			temp->arg1 = i;
			temp->next = curOP;
			curOP = temp;
            
            temp = new OPInfo;
            temp->type = GETOBJCOLOR;
            temp->arg1 = i;
            temp->next = curOP;
            curOP = temp;
            
			temp = new OPInfo;
			temp->type = REMOVEOBJ;
			temp->arg1 = i;
			temp->next = curOP;
			curOP = temp;
            
            temp = new OPInfo;
            temp->type = GETOBJCOLOR;
            temp->arg1 = i;
            temp->next = curOP;
            curOP = temp;
            
            totalProcess += 4;
		}
    }
    
 /*   temp = new OPInfo;
    temp->type = INITOBJ;
    temp->next = curOP;
    curOP = temp;*/
    
    temp = new OPInfo;
    temp->type = INITBACE;
    temp->next = curOP;
    curOP = temp;
    
    totalProcess++;
    
	//init light
	if(lightCount > 0){
		for(int i=0;i<lightCount;i++){
			temp = new OPInfo;
			temp->type = ADDLIGHT;
			temp->arg1 = i;
			temp->next = curOP;
			curOP = temp;
            
            totalProcess++;
		}
	}
    else{
		temp = new OPInfo;
		temp->type = ADDLIGHT;
		temp->arg1 = 0;
		temp->next = curOP;
		curOP = temp;
        
        totalProcess++;
	}
    
	temp = new OPInfo;
	temp->type = CLEAR;
	temp->next = curOP;
	curOP = temp;
    
    totalProcess++;
    
	return true;
}

//add light l to lightTex
bool HelloWorld::addLight(lightInfo *l){
	if(!l)
		return false;
    
	if(!l->bace){
		char *temp = getFilePath(l->lightFile);
        
        Array2D<myPixel> mp;
        int iw,ih;
        readImage(temp, mp, iw, ih);
        float *pixels = (float*)getPixelData(mp, iw, ih);
      //  l->bace = new exrTexture();
        l->bace = pixels;
        
		free(temp);
		if(l->bace == NULL)
			return false;
	}
    
    Sprite *s = (Sprite*)this->getChildByTag(picTag);
    int width = s->getContentSize().width;
    int height = s->getContentSize().height;
    int offset = 0;
    float r = l->intensity*l->rgb[0];
    float g = l->intensity*l->rgb[1];
    float b = l->intensity*l->rgb[2];
    for(int i=0;i<height;i++)
        for (int j=0; j<width; j++) {
            light->_imageData[offset] += l->bace[offset]*r;
            light->_imageData[offset+1] += l->bace[offset+1]*g;
            light->_imageData[offset+2] += l->bace[offset+2]*b;
            light->_imageData[offset+3] = 1.0;
            offset += 4;
        }
    
    lightUpdated = true;
    
    free(l->bace);
    l->bace = nullptr;
   // l->baceTex->release();
    
//	state->setUniformInt(STATE,5);
//	state->setUniformTexture(LIGHT,l->bace);
//	state->setUniformTexture(BACE,light);
//	state->setUniformVec4(COLOR,cocos2d::Vec4(l->rgb[0],l->rgb[1],l->rgb[2],l->intensity));
    
	return true;
}

//remove light l from lightTex
bool HelloWorld::removeLight(lightInfo *l){
	if(!l)
		return false;
    
	if(!l->bace){
		char *temp = getFilePath(l->lightFile);
        
        Array2D<myPixel> mp;
        int iw,ih;
        readImage(temp, mp, iw, ih);
        float *pixels = (float*)getPixelData(mp, iw, ih);
      //  l->bace = new exrTexture();
        l->bace = pixels;
        exrTexture *tex = new exrTexture();
        tex->retain();
        tex->autorelease();
        tex->initWithExrData(iw, ih, pixels, true);
        l->baceTex = tex;
        
		//l->bace = loadTex(temp);
		free(temp);
		if(l->bace == NULL)
			return false;
	}
    
    Sprite *s = (Sprite*)this->getChildByTag(picTag);
    int width = s->getContentSize().width;
    int height = s->getContentSize().height;
    int offset = 0;
    float r = l->intensity*l->rgb[0];
    float g = l->intensity*l->rgb[1];
    float b = l->intensity*l->rgb[2];
    for(int i=0;i<height;i++)
        for (int j=0; j<width; j++) {
            light->_imageData[offset] -= l->bace[offset]*r;
            light->_imageData[offset+1] -= l->bace[offset+1]*g;
            light->_imageData[offset+2] -= l->bace[offset+2]*b;
            offset += 4;
        }
    
    lightUpdated = true;
    
	return true;
}

bool HelloWorld::getObjColor(objInfo *o){
    if(!o)
        return false;
    
    if(!o->objBace){
        char *temp = getFilePath(o->baceFile);
        o->objBace = loadTex(temp);
        free(temp);
        if(o->objBace == NULL)
            return false;
    }
    if(!o->UV){
        char *temp = getFilePath(o->uvFile);
        o->UV = loadTex(temp);
        free(temp);
        if(o->UV == NULL)
            return false;
    }
    
    if(o->tex){
        state->setUniformInt(STATE, 11);
        state->setUniformTexture(TEX, o->tex);
    }
    else
        state->setUniformInt(STATE, 10);
    
    state->setUniformTexture(ORIGIN,bace);
    state->setUniformTexture(BACE,objALL);  //this line should be delete soon
    state->setUniformTexture(OBJUV,o->UV);
    state->setUniformTexture(OBJBACE,o->objBace);
    state->setUniformVec4(COLOR,cocos2d::Vec4(o->rgb[0],o->rgb[1],o->rgb[2],1));
    
    return true;
}

bool HelloWorld::addObj(objInfo *o){
	if(!o)
		return false;
    
    int off = 0;
    for(int i=0;i<originHeight;i++)
        for(int j=0;j<originWidth;j++,off+=4){
            objALL->_imageData[off] += objSingle->_imageData[off];
            objALL->_imageData[off+1] += objSingle->_imageData[off+1];
            objALL->_imageData[off+2] += objSingle->_imageData[off+2];
            objALL->_imageData[off+3] = 1.0;
        }
    
	return true;
}

bool HelloWorld::removeObj(objInfo *o){
	if(!o)
		return false;
    
	if(!o->objBace){
		char *temp = getFilePath(o->baceFile);
		o->objBace = loadTex(temp);
		free(temp);
		if(o->objBace == NULL)
			return false;
	}
	if(!o->UV){
		char *temp = getFilePath(o->uvFile);
		o->UV = loadTex(temp);
		free(temp);
		if(o->UV == NULL)
			return false;
	}
    
    int off = 0;
    for(int i=0;i<originHeight;i++)
        for(int j=0;j<originWidth;j++,off+=4){
            objALL->_imageData[off] -= objSingle->_imageData[off];
            objALL->_imageData[off+1] -= objSingle->_imageData[off+1];
            objALL->_imageData[off+2] -= objSingle->_imageData[off+2];
            objALL->_imageData[off+3] = 1.0;
        }
    
	/*if(o->tex){
		state->setUniformInt(STATE,4);
		state->setUniformTexture(TEX,o->tex);
	}
	else
		state->setUniformInt(STATE,8);
    
	state->setUniformTexture(ORIGIN,bace);
	state->setUniformTexture(BACE,objALL);
	state->setUniformTexture(OBJUV,o->UV);
	state->setUniformTexture(OBJBACE,o->objBace);
	state->setUniformVec4(COLOR,cocos2d::Vec4(o->rgb[0],o->rgb[1],o->rgb[2],1));
*/
//	Sprite *p = (Sprite*)this->getChildByTag(picTag);
    
//	myRTT->begin();
//	p->visit();
//	myRTT->end();
    
	return true;
}

//for modifying light intensity.
//remove target light from lightmap and change shader state
bool HelloWorld::setCurLight(int lightNum){
    if(curLight && curLight == lights[lightNum])
        return false;
    
	int num = -1;
	int num2 = -1;
    
	if(curObj){
		for(int i=0;i<objCount;i++){
			if(objects[i] == curObj){
				num2 = i;
				break;
			}
		}
        
		curObj = nullptr;
	}
    
	if(curLight){
		for(int i=0;i<lightCount;i++)
			if(lights[i] == curLight){
				num = i;
				break;
			}
	}
	curLight = lights[lightNum];
    
	OPInfo *temp = new OPInfo;
    
	temp->next = curOP;
	temp->type = NORMALLIGHT;
	temp->arg1 = lightNum;
	curOP = temp;
    totalProcess++;
    
	temp = new OPInfo;
	temp->next = curOP;
	temp->type = REMOVELIGHT;
	temp->arg1 = lightNum;
	curOP = temp;
    totalProcess++;
    
	if(num != -1){
        temp = new OPInfo;
        temp->next = curOP;
        temp->type = CHANGE;
        temp->arg1 = 0;
        temp->arg2 = num;
        curOP = temp;
        
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDLIGHT;
		temp->arg1 = num;
		curOP = temp;
        totalProcess++;
	}
    
	if(num2 != -1){
        temp = new OPInfo;
        temp->next = curOP;
        temp->type = CHANGE;
        temp->arg1 = 2;
        temp->arg2 = num2;
        curOP = temp;
        
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDOBJ;
		temp->arg1 = num2;
		curOP = temp;
        
        temp = new OPInfo;
        temp->type = GETOBJCOLOR;
        temp->arg1 = num2;
        temp->next = curOP;
        curOP = temp;
        totalProcess += 2;
    }
    
    csL->setValue(curLight->intensity);
    
    swallow->swallow();
    
	return true;
}

//set current object to obj and set shader uniform
bool HelloWorld::setCurObj(int objNum){
    if(curObj && curObj == objects[objNum])
        return false;
    
	int num = -1;
	int num2 = -1;
    
	if(curLight){
		for(int i=0;i<lightCount;i++){
			if(lights[i] == curLight){
				num2 = i;
				break;
			}
		}
        
		curLight = nullptr;
	}
    
	if(curObj){
		for(int i=0;i<objCount;i++)
			if(objects[i] == curObj){
				num = i;
				break;
			}
	}
	curObj = objects[objNum];
    
	OPInfo *temp = new OPInfo;
    
	temp->next = curOP;
	temp->type = NORMALOBJ;
	temp->arg1 = objNum;
	curOP = temp;
    totalProcess++;
    
	temp = new OPInfo;
	temp->next = curOP;
	temp->type = REMOVEOBJ;
	temp->arg1 = objNum;
	curOP = temp;
    
    temp = new OPInfo;
    temp->type = GETOBJCOLOR;
    temp->arg1 = objNum;
    temp->next = curOP;
    curOP = temp;
    totalProcess += 2;
    
	if(num != -1){
        temp = new OPInfo;
        temp->next = curOP;
        temp->type = CHANGE;
        temp->arg1 = 3;
        temp->arg2 = num;
        curOP = temp;
        
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDOBJ;
		temp->arg1 = num;
		curOP = temp;
        
        temp = new OPInfo;
        temp->type = GETOBJCOLOR;
        temp->arg1 = num;
        temp->next = curOP;
        curOP = temp;
        totalProcess += 2;
	}
    
	if(num2 != -1){
        temp = new OPInfo;
        temp->next = curOP;
        temp->type = CHANGE;
        temp->arg1 = 1;
        temp->arg2 = num2;
        curOP = temp;
        
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDLIGHT;
		temp->arg1 = num2;
		curOP = temp;
        totalProcess++;
	}
    
    swallow->swallow();
    
    return true;
}

//load .exr texture
exrTexture * HelloWorld::loadTex(const char *path, bool inMem){
 //   return Director::getInstance()->getTextureCache()->addImage(path);
    
    Array2D<myPixel> mp;
    int iw,ih;
    
    readImage(path, mp, iw, ih);
    float *pixels = (float*)getPixelData(mp, iw, ih);
    exrTexture *etex = new exrTexture();
    etex->autorelease();
    etex->retain();
    if(!inMem){
        etex->initWithExrData(iw, ih, pixels, true);
        free(pixels);
        etex->_imageData = nullptr;
    }
    else
        etex->_imageData = pixels;
    
    return etex;
}

//load user texture which is .png and .jpg
Texture2D *HelloWorld::loadUserTex(const char* filename){
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
	std::string fullpath = filename;
	fullpath = texturePath+"Textures/"+fullpath;
	return Director::getInstance()->getTextureCache()->addImage(fullpath);
}

void HelloWorld::useShader(Sprite *sprite){
	if(sprite){
		GLProgram * p = new GLProgram();
		p->initWithFilenames("myShader.vsh", "myShader.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
		p->link();
		p->updateUniforms();
		sprite->setShaderProgram(p);
	}
}

void HelloWorld::userShaderRGB(Sprite *sprite){
	if(sprite){
		GLProgram * p = new GLProgram();
		p->initWithFilenames("rgbShader.vsh", "rgbShader.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
		p->link();
		p->updateUniforms();
		sprite->setShaderProgram(p);
        BlendFunc blf = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
        sprite->setBlendFunc(blf);
    //    sprite->setb
	}
}

void HelloWorld::objectEditAni(){
    playingAni = false;
    
    OPInfo *temp = new OPInfo;
    temp->type = EMPTY;
    temp->next = curOP;
    curOP = temp;
    this->scheduleUpdate();
}

void HelloWorld::emptyAni(){
    playingAni = false;
    return;
}

void HelloWorld::objectItem(Ref *pSender,Widget::TouchEventType event){
    if (event == Widget::TouchEventType::BEGAN) {
        Button *b = (Button*)pSender;
        b->setTitleColor(Color3B::WHITE);
        b->loadTextures("icon/main-edit-comp-pressed.png", "icon/main-edit-comp-pressed.png");
        return;
    }
    if (event == Widget::TouchEventType::CANCELED) {
        Button *b = (Button*)pSender;
        b->setTitleColor(Color3B::BLACK);
        b->loadTextures("icon/main-edit-comp-normal.png", "icon/main-edit-comp-normal.png");
        return;
    }
    if (event != Widget::TouchEventType::ENDED) {
        return;
    }
    static int choosed = 0;
    if(viewChanged){
        choosed = 0;
        viewChanged = false;
    }
    
    Button *b = (Button*)pSender;
    
    auto label = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout, "Label_objName");
    string text = b->getTitleText();
//    text = text + "颜色";
    label->setString(text);
    auto bg = Helper::seekWidgetByName(uiLayout, "Image_objName");
    bg->setContentSize(cocos2d::Size(label->getContentSize().width+20,40));
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_editPanel_in");

    Button *prev = (Button*)objectList->getChildByTag(choosed)->getChildByTag(choosed);
    prev->setTitleColor(Color3B::BLACK);
    prev->loadTextures("icon/main-edit-comp-normal.png", "icon/main-edit-comp-pressed.png");
    
    b->setTitleColor(Color3B::WHITE);
    b->loadTextures("icon/main-edit-comp-pressed.png", "icon/main-edit-comp-pressed.png");
    
    int num = b->getTag();
    CCLog("num:%d\n",num);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setVisible(false);
    csL->setEnabled(false);
    csR->setEnabled(false);
    csG->setEnabled(false);
    csB->setEnabled(false);
    if(num == choosed){
        ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
        
        if(num < objCount){
            Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(true);
            Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(false);
            Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(true);
            Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(false);
            ((Button*)Helper::seekWidgetByName(uiLayout, "Button_texTab"))->setEnabled(true);
            Helper::seekWidgetByName(uiLayout, "Image_texTab")->setVisible(true);
            ((Button*)Helper::seekWidgetByName(uiLayout, "Button_lightTab"))->setEnabled(false);
            Helper::seekWidgetByName(uiLayout, "Image_lightTab")->setVisible(false);
        }
        else{
            csL->setEnabled(true);
            Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(false);
            Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(true);
            Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(false);
            Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(true);
            ((Button*)Helper::seekWidgetByName(uiLayout, "Button_texTab"))->setEnabled(false);
            Helper::seekWidgetByName(uiLayout, "Image_texTab")->setVisible(false);
            ((Button*)Helper::seekWidgetByName(uiLayout, "Button_lightTab"))->setEnabled(true);
            Helper::seekWidgetByName(uiLayout, "Image_lightTab")->setVisible(true);
        }
        return;
    }
    
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::objectEditAni, this)));
    
    choosed = num;
    
    if(num < objCount){
        Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(true);
        Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(false);
        Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(true);
        Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(false);
        ((Button*)Helper::seekWidgetByName(uiLayout, "Button_texTab"))->setEnabled(true);
        Helper::seekWidgetByName(uiLayout, "Image_texTab")->setVisible(true);
        ((Button*)Helper::seekWidgetByName(uiLayout, "Button_lightTab"))->setEnabled(false);
        Helper::seekWidgetByName(uiLayout, "Image_lightTab")->setVisible(false);
        setCurObj(num);
    }
    else{
        csL->setEnabled(true);
        Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(false);
        Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(true);
        Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(false);
        Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(true);
        ((Button*)Helper::seekWidgetByName(uiLayout, "Button_texTab"))->setEnabled(false);
        Helper::seekWidgetByName(uiLayout, "Image_texTab")->setVisible(false);
        ((Button*)Helper::seekWidgetByName(uiLayout, "Button_lightTab"))->setEnabled(true);
        Helper::seekWidgetByName(uiLayout, "Image_lightTab")->setVisible(true);
        setCurLight(num-objCount);
    //    sL->setPercent(100*lights[num-objCount]->intensity);
    }
    
    swallow->swallow();
   // this->addChild(swallow,100);
    
    renderSprite->setVisible(true);
  //  this->scheduleUpdate();
}

void HelloWorld::sceneItem(Ref *pSender,Widget::TouchEventType event){

}

void HelloWorld::onExit(){
    Layer::onExit();
    
    for(int i=0;i<objCount;i++){
        if(objects[i]->objBace){
            objects[i]->objBace->release();
            if(objects[i]->objBace->_imageData)
                free(objects[i]->objBace->_imageData);
        }
        if(objects[i]->UV){
            objects[i]->UV->release();
            if(objects[i]->UV->_imageData)
                free(objects[i]->UV->_imageData);
        }
        free(objects[i]->baceFile);
        free(objects[i]->objName);
        free(objects[i]->uvFile);
        free(objects[i]);
    }
    delete objects;
    if(lightCount == 0){
        if (lights[0]->bace) {
            free(lights[0]->bace);
        }
        if(lights[0]->baceTex)
            lights[0]->baceTex->release();
        free(lights[0]);
    }
    for(int i=0;i<lightCount;i++){
        if (lights[i]->bace) {
            free(lights[i]->bace);
        }
        if(lights[i]->baceTex)
            lights[i]->baceTex->release();
        free(lights[i]->lightFile);
        free(lights[i]->lightName);
        free(lights[i]);
    }
    delete lights;
    
    if (light->_imageData)
        free(light->_imageData);
    
    if(objALL->_imageData)
        free(objALL->_imageData);
    
    if(objSingle->_imageData)
        free(objSingle->_imageData);
    
    light->release();
    bace->release();
    objALL->release();
    oLight->release();
  //  shot->release();
    objSingle->release();
    
    for(int i=0;i<viewNum;i++)
        free(eyeViews[i]);
    delete eyeViews;
    
    free(filepath);
    
    ActionManagerEx::getInstance()->releaseActions();
    Director::getInstance()->getTextureCache()->removeAllTextures();
}

void HelloWorld::retAni(){
    Director::getInstance()->popScene();
}

void funCallback()
{
    return;
}

void HelloWorld::bScene(Object *sender,TouchEventType eventType){
    if(eventType == TouchEventType::TOUCH_EVENT_ENDED && !retPressed){
        retPressed = true;
        CallFunc *func = CallFunc::create(CC_CALLBACK_0(HelloWorld::retAni, this));
        ani_ret->play(func);
    }
    else if (eventType == TouchEventType::TOUCH_EVENT_BEGAN)
        ani_ret->play();
    else if(eventType == TouchEventType::TOUCH_EVENT_CANCELED)
        ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_ret_cancel");

   // ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_return");
    
  //  Director::getInstance()->popScene();
}

void HelloWorld::bReset(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    if(curObj){
        curObj->rgb[0] = curObj->originRGB[0];
        curObj->rgb[1] = curObj->originRGB[1];
        curObj->rgb[2] = curObj->originRGB[2];
        
        showState->setUniformVec4(COLOR,cocos2d::Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
        stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        
        csR->setValue(curObj->rgb[0]);
        csG->setValue(curObj->rgb[1]);
        csB->setValue(curObj->rgb[2]);
        
        curObj->texName = curObj->originTexName;
        if(curObj->texName != ""){
            curObj->tex = loadUserTex(curObj->texName.c_str());
            showState->setUniformTexture(TEX, curObj->tex);
        }
        else{
            curObj->tex = NULL;
            Director::getInstance()->getTextureCache()->removeUnusedTextures();
            if(lightCount > 0)
                showState->setUniformInt(STATE,0);
            else
                showState->setUniformInt(STATE,-2);
        }
    }
    else{
        curLight->rgb[0] = curLight->originRGB[0];
        curLight->rgb[1] = curLight->originRGB[1];
        curLight->rgb[2] = curLight->originRGB[2];
        curLight->intensity = curLight->originIntensity;
        
        showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
        stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        
        csR->setValue(curLight->rgb[0]);
        csG->setValue(curLight->rgb[1]);
        csB->setValue(curLight->rgb[2]);
        csL->setValue(curLight->intensity);
    }
    
    //ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_editPanel_out");
}

void HelloWorld::bEditDone(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_editPanel_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
}

void HelloWorld::bObject(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_btn3_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_objPanel_in");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    
  /*  if(curView != 0)
		panels[curView]->setVisible(false);
    csR->setVisible(false);
    csG->setVisible(false);
    csB->setVisible(false);
    csL->setVisible(true);
    
 //   viewList->setVisible(false);
    
	panels[0]->setVisible(true);
    
	curView = 0;*/
}

void HelloWorld::bObjectActive(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_btn3_in");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_objPanel_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
}

void HelloWorld::bLight(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setEnabled(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(true);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(true);
    csL->setEnabled(true);
    csR->setEnabled(false);
    csG->setEnabled(false);
    csB->setEnabled(false);
    
    string text = curLight->lightName;
    auto label = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout, "Label_objName");
    label->setString(text);
    auto bg = Helper::seekWidgetByName(uiLayout, "Image_objName");
    bg->setContentSize(cocos2d::Size(label->getContentSize().width+20,40));
    
    return;
}

void HelloWorld::bColor(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setVisible(true);
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setEnabled(true);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(false);
    csL->setEnabled(false);
    csR->setEnabled(true);
    csG->setEnabled(true);
    csB->setEnabled(true);
    
    string text;
    if(curObj)
        text = curObj->objName;
    else
        text = curLight->lightName;
    auto label = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout, "Label_objName");
    text = text + "颜色";
    label->setString(text);
    auto bg = Helper::seekWidgetByName(uiLayout, "Image_objName");
    bg->setContentSize(cocos2d::Size(label->getContentSize().width+20,40));
    
    return;
    
	if(curView != 1)
		panels[curView]->setVisible(false);
    
	panels[1]->setVisible(true);
    csR->setVisible(true);
    csG->setVisible(true);
    csB->setVisible(true);
    csL->setVisible(false);
    
  //  viewList->setVisible(false);
    
	if(curObj){
		stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
	}
	else if(curLight){
		stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
	}
    
	curView = 1;
}

void HelloWorld::bTexture(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setVisible(true);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setVisible(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editColor")->setEnabled(false);
    Helper::seekWidgetByName(uiLayout, "Panel_editTexture")->setEnabled(true);
    Helper::seekWidgetByName(uiLayout, "Panel_editLight")->setEnabled(false);
    csL->setEnabled(false);
    csR->setEnabled(false);
    csG->setEnabled(false);
    csB->setEnabled(false);
    
    string text = curObj->objName;
    auto label = (cocos2d::ui::Text*)Helper::seekWidgetByName(uiLayout, "Label_objName");
    label->setString(text);
    auto bg = Helper::seekWidgetByName(uiLayout, "Image_objName");
    bg->setContentSize(cocos2d::Size(label->getContentSize().width+20,40));
    
    return;
    
	if(curView != 2)
		panels[curView]->setVisible(false);
    csR->setVisible(false);
    csG->setVisible(false);
    csB->setVisible(false);
    csL->setVisible(false);
    
 //   viewList->setVisible(false);
    
	panels[2]->setVisible(true);
    
	curView = 2;
}

void HelloWorld::bSave(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    return;
    
    NSMutableString *data = [[NSMutableString alloc] initWithCapacity:10];
    
    //objects
    [data setString:[NSString stringWithFormat:@"%d\r\n",objCount]];
    for(int i=0;i<objCount;i++){
        //object name
        [data appendString:@"\""];
        [data appendString:[NSString stringWithCString:objects[i]->objName encoding:NSUTF8StringEncoding]];
        [data appendString:@"\"\r\n"];
        //object bace file
        [data appendString:@"\""];
        [data appendString:[NSString stringWithCString:objects[i]->baceFile encoding:NSUTF8StringEncoding]];
        [data appendString:@"\"\r\n"];
        //object shader file
        [data appendString:@"\""];
        [data appendString:[NSString stringWithCString:objects[i]->uvFile encoding:NSUTF8StringEncoding]];
        [data appendString:@"\"\r\n"];
        //object color
        int colorR,colorG,colorB;
        if(objects[i]->tempRGB[0] != -1){
            colorR = 255*objects[i]->tempRGB[0];
            colorG = 255*objects[i]->tempRGB[1];
            colorB = 255*objects[i]->tempRGB[2];
        }
        else{
            colorR = 255*objects[i]->rgb[0];
            colorG = 255*objects[i]->rgb[1];
            colorB = 255*objects[i]->rgb[2];
        }
        [data appendString:[NSString stringWithFormat:@"(color %d %d %d)\r\n",colorR,colorG,colorB]];
        //object texture
        if (objects[i]->tex) {
            [data appendString:[NSString stringWithCString:objects[i]->texName.c_str() encoding:NSUTF8StringEncoding]];
            [data appendString:@"\r\n"];
        }
        else
            [data appendString:@"0\r\n"];
    }
    
    //lights
    [data appendString:[NSString stringWithFormat:@"%d\r\n",lightCount]];
    for(int i=0;i<lightCount;i++){
        [data appendString:[NSString stringWithFormat:@"\"%s\"\r\n\"%s\"\r\n",lights[i]->lightName,lights[i]->lightFile]];
        [data appendString:[NSString stringWithFormat:@"(color %d %d %d)\r\n",(int)lights[i]->rgb[0]*255,(int)lights[i]->rgb[1]*255,(int)lights[i]->rgb[2]*255]];
        [data appendString:[NSString stringWithFormat:@"%d\r\n",(int)(lights[i]->intensity*100)]];
    }
    
    [data writeToFile:[NSString stringWithFormat:@"%s",sceneFile.c_str()] atomically:YES];
    
    return;
}

void HelloWorld::bViewActive(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_btn3_in");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_viewPanel_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
}

void HelloWorld::bView(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_btn3_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_viewPanel_in");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
  /*  panels[curView]->setVisible(false);
    csR->setVisible(false);
    csG->setVisible(false);
    csB->setVisible(false);
    csL->setVisible(false);
  //  viewList->setVisible(true);
    panels[3]->setVisible(true);
    curView = 3;
    */
    return;
    
 /*   if(curObj){
        if (!oldObj) {
            return;
        }
        
        newObj = curObj;
        
        //if texture changed
        if(curObj->tex != oldObj->tex){
            if(oldObj->tex){
                if(lightCount>0)
                    state->setUniformInt(STATE, 1);
                else
                    state->setUniformInt(STATE, -1);
                
                state->setUniformTexture(TEX, oldObj->tex);
            }
            else{
                if(lightCount>0)
                    state->setUniformInt(STATE, 0);
                else
                    state->setUniformInt(STATE, -2);
            }
        }
        
        //if color changed
        else{
            sR->setPercent(oldObj->rgb[0]*100);
            sG->setPercent(oldObj->rgb[1]*100);
            sB->setPercent(oldObj->rgb[2]*100);
            
            state->setUniformVec4(COLOR,cocos2d::Vec4(oldObj->rgb[0],oldObj->rgb[1],oldObj->rgb[2],1));
            stateColor->setUniformVec3("rgb",cocos2d::Vec3(oldObj->rgb[0],oldObj->rgb[1],oldObj->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(oldObj->rgb[0],oldObj->rgb[1],oldObj->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(oldObj->rgb[0],oldObj->rgb[1],oldObj->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(oldObj->rgb[0],oldObj->rgb[1],oldObj->rgb[2]));
        }
        
        curObj = oldObj;
        oldObj = nullptr;
        return;
    }
    
    else if (curLight){
        if(!oldLight)
            return;
        
        newLight = curLight;
        
        sR->setPercent(oldLight->rgb[0]*100);
        sG->setPercent(oldLight->rgb[1]*100);
        sB->setPercent(oldLight->rgb[2]*100);
        
        state->setUniformVec4(COLOR,cocos2d::Vec4(oldLight->rgb[0],oldLight->rgb[1],oldLight->rgb[2],oldLight->intensity));
        stateColor->setUniformVec3("rgb",cocos2d::Vec3(oldLight->rgb[0],oldLight->rgb[1],oldLight->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(oldLight->rgb[0],oldLight->rgb[1],oldLight->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(oldLight->rgb[0],oldLight->rgb[1],oldLight->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(oldLight->rgb[0],oldLight->rgb[1],oldLight->rgb[2]));
        
        curLight = oldLight;
        oldLight = nullptr;
    }*/
}

//not complete
void HelloWorld::bRedo(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
  /*  if(curObj){
        if (!newObj) {
            return;
        }
        
        oldObj = curObj;
        
        //if texture changed
        if(curObj->tex != newObj->tex){
            if(newObj->tex){
                if(lightCount>0)
                    state->setUniformInt(STATE, 1);
                else
                    state->setUniformInt(STATE, -1);
                
                state->setUniformTexture(TEX, newObj->tex);
            }
            else{
                if(lightCount>0)
                    state->setUniformInt(STATE, 0);
                else
                    state->setUniformInt(STATE, -2);
            }
        }
        
        //if color changed
        else{
            sR->setPercent(newObj->rgb[0]*100);
            sG->setPercent(newObj->rgb[1]*100);
            sB->setPercent(newObj->rgb[2]*100);
            
            state->setUniformVec4(COLOR,cocos2d::Vec4(newObj->rgb[0],newObj->rgb[1],newObj->rgb[2],1));
            stateColor->setUniformVec3("rgb",cocos2d::Vec3(newObj->rgb[0],newObj->rgb[1],newObj->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(newObj->rgb[0],newObj->rgb[1],newObj->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(newObj->rgb[0],newObj->rgb[1],newObj->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(newObj->rgb[0],newObj->rgb[1],newObj->rgb[2]));
        }
        
        curObj = newObj;
        newObj = nullptr;
        return;
    }
    
    else if (curLight){
        if(!newLight)
            return;
        
        oldLight = curLight;
        
        state->setUniformVec4(COLOR,cocos2d::Vec4(newLight->rgb[0],newLight->rgb[1],newLight->rgb[2],newLight->intensity));
        stateColor->setUniformVec3("rgb",cocos2d::Vec3(newLight->rgb[0],newLight->rgb[1],newLight->rgb[2]));
        stateR->setUniformVec3("rgb",cocos2d::Vec3(newLight->rgb[0],newLight->rgb[1],newLight->rgb[2]));
        stateG->setUniformVec3("rgb",cocos2d::Vec3(newLight->rgb[0],newLight->rgb[1],newLight->rgb[2]));
        stateB->setUniformVec3("rgb",cocos2d::Vec3(newLight->rgb[0],newLight->rgb[1],newLight->rgb[2]));
        
        sR->setPercent(newLight->rgb[0]*100);
        sG->setPercent(newLight->rgb[1]*100);
        sB->setPercent(newLight->rgb[2]*100);
        
        curLight = newLight;
        newLight = nullptr;
    }*/
}

void HelloWorld::bFullScreen(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    if(playingAni)
        return;
    playingAni = true;
    
    auto ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_btn3_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    ani = ActionManagerEx::getInstance()->getActionByName(JSON, "Ani_top2_out");
    ani->play(CallFunc::create(CC_CALLBACK_0(HelloWorld::emptyAni, this)));
    
    ((Button*)Helper::seekWidgetByName(uiLayout,"Button_full_ret"))->setEnabled(true);
    
    if(Helper::seekWidgetByName(uiLayout, "Image_name")->getContentSize().height == 225)
        bSceneInfo(Helper::seekWidgetByName(uiLayout, "Button_title"), cocos2d::ui::TOUCH_EVENT_ENDED);
}

void HelloWorld::bFullScreenRet(Object *sender,TouchEventType eventType){
    if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
        return;
    
    ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_btn3_in");
    ActionManagerEx::getInstance()->playActionByName(JSON, "Ani_top2_in");
    
    ((Button*)sender)->setEnabled(false);
}

void HelloWorld::getSceneFiles(){
    NSFileManager *tempFM = [NSFileManager defaultManager];
//    NSString *dirpath = [@SCENEPATH stringByExpandingTildeInPath];
 /*   NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    NSString *docs = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    NSString *dirpath = [docs stringByAppendingPathComponent:@"scenes"];
    
    scenePath = [dirpath UTF8String];
    scenePath = scenePath + "/";
    */
    NSDirectoryEnumerator *direnum = [tempFM enumeratorAtPath:[NSString stringWithCString:scenePath.c_str() encoding:NSUTF8StringEncoding]];
    NSMutableArray *files = [NSMutableArray arrayWithCapacity:5];
    NSString *filename;
    while(filename = [direnum nextObject]){
        if ([[filename pathExtension] isEqualToString:@"txt"]) {
            [files addObject:filename];
        }
    }
    
    NSEnumerator *fileenum = [files objectEnumerator];
    int l = (int)[files count];
    
    if (sceneName) {
        for(int i=0;i<sceneCount;i++)
            free(sceneName[i]);
        free(sceneName);
    }
    
    char **ret = nullptr;
    ret = (char**)malloc(sizeof(char*)*sceneCount);
    int i = 0;
    std::string temp[10];
    while (filename = [fileenum nextObject]) {
        const char *name = [filename UTF8String];
        char * end = strchr(name, '/');
        if(end)
            continue;
        
        end = strrchr(name,'.');
        ret[i] = (char*)malloc(end-name+1);
        *end = 0;
        int sl = strlen(name);
        memcpy(ret[i], name, strlen(name)+1);
        //ret[i][end-name] = 0;
        
        temp[i] = ret[i];
        
        i++;
    }
    
    sceneName = ret;
    sceneCount = i;
}

void HelloWorld::update(float dt){
  /*  static bool done = false;
    static exrTexture *tex = new exrTexture;
    
    if(done){
        cocos2d::Size size = Director::getInstance()->getVisibleSize();
        
        Sprite* s = Sprite::createWithTexture(tex);
        s->setPosition(size.width/2, size.height/2);
        s->setScale(0.3);
        this->addChild(s,5);

        this->unscheduleUpdate();
    }
    if(!done){
        capture(tex,spriteX,spriteY,spriteW,spriteH);
        done = true;
    }
    return;*/
    
 //   loadSprite->tex = NULL;
	OPInfo *old;
    static int c=0;
    static bool init = true;
	switch(curOP->type){
        case EMPTY:
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            break;
        case CHANGE:
            // arg1 = 0 : light to light
            // arg1 = 1 : light to object
            // arg1 = 2 : object to light
            // arg1 = 3 : object to object
            // arg2 : previous object or light
            if(curOP->arg1 < 2){
                lights[curOP->arg2]->baceTex->release();
                lights[curOP->arg2]->baceTex = nullptr;
                
                light->initWithExrData(originWidth, originHeight, light->_imageData, true);
                if(curOP->arg1 == 0){
                    lightInfo *l = curLight;
                    if(!l->bace){
                        char *temp = getFilePath(l->lightFile);
                        
                        Array2D<myPixel> mp;
                        int iw,ih;
                        readImage(temp, mp, iw, ih);
                        float *pixels = (float*)getPixelData(mp, iw, ih);
                        l->bace = pixels;
                        exrTexture *tex = new exrTexture();
                        tex->autorelease();
                        tex->retain();
                        tex->initWithExrData(iw, ih, pixels, true);
                        l->baceTex = tex;
                        
                        free(temp);
                    }
                    showState->setUniformTexture(LIGHT, curLight->baceTex);
                    showState->setUniformVec4(COLOR,cocos2d::Vec4(1,1,1,1));
                }
                else{
                    objInfo *o = curObj;
                    if(!o->objBace){
                        char *temp = getFilePath(o->baceFile);
                        o->objBace = loadTex(temp);
                        free(temp);
                    }
                    showState->setUniformInt(STATE, 0);
                    showState->setUniformTexture(LIGHT, light);
                    showState->setUniformTexture(BACE,objALL);
                    showState->setUniformTexture(ORIGIN,bace);
                    showState->setUniformTexture(ORIGINLIGHT, oLight);
               //     showState->setUniformTexture(OBJUV,curObj->UV);
                    showState->setUniformTexture(OBJBACE,curObj->objBace);
                    showState->setUniformVec4(COLOR,cocos2d::Vec4(1,1,1,1));
                    
                }
            }
            else{
                objInfo *p = objects[curOP->arg2];
                p->objBace->release();
                p->objBace = nullptr;
                p->UV->release();
                p->UV = nullptr;
                
                objALL->initWithExrData(originWidth, originHeight, objALL->_imageData, true);
                
                if(curOP->arg1 == 3){
                    objInfo *o = curObj;
                    if(!o->objBace){
                        char *temp = getFilePath(o->baceFile);
                        o->objBace = loadTex(temp);
                        free(temp);
                    }
                    
                    if(lightCount > 0){
                        showState->setUniformInt(STATE,0);
                    }
                    else{
                        showState->setUniformInt(STATE,-2);
                    }
                    showState->setUniformVec4(COLOR,cocos2d::Vec4(1,1,1,1));
                    showState->setUniformTexture(OBJBACE, curObj->objBace);
                }
                else{
                    lightInfo *l = curLight;
                    if(!l->bace){
                        char *temp = getFilePath(l->lightFile);
                        
                        Array2D<myPixel> mp;
                        int iw,ih;
                        readImage(temp, mp, iw, ih);
                        float *pixels = (float*)getPixelData(mp, iw, ih);
                        l->bace = pixels;
                        exrTexture *tex = new exrTexture();
                        tex->autorelease();
                        tex->retain();
                        tex->initWithExrData(iw, ih, pixels, true);
                        l->baceTex = tex;
                        
                        free(temp);
                    }
                    
                    showState->setUniformInt(STATE,2);
                    showState->setUniformTexture(BACE,light);
                    showState->setUniformTexture(LIGHT,curLight->baceTex);
                    showState->setUniformTexture(ORIGINLIGHT,oLight);
                    showState->setUniformTexture(OBJBACE,objALL);
                    showState->setUniformVec4(COLOR,cocos2d::Vec4(1,1,1,1));
                }
                
            }
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;
        case GETOBJCOLOR:
            //test
            getObjColor(objects[curOP->arg1]);
      //      if(objSingle->_imageData)
       //         free(objSingle->_imageData);
            capture(objSingle, 0, 0, spriteW, spriteH, ORDER, true);
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;
        case INITBACE:{
            c++;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            if(lightUpdated){
                light->initWithExrData(originWidth, originHeight, light->_imageData, true);
                lightUpdated = false;
            }
            oLight->initWithExrData(originWidth, originHeight, light->_imageData, true);
            
            Array2D<myPixel> mp;
            int iw,ih;
            
            char *baceFile = getFilePath(BACEFILE);
            readImage(baceFile, mp, iw, ih);
            float *pixels = (float*)getPixelData(mp, iw, ih);
            
            bace->initWithExrData(iw, ih, pixels, true);
            objALL->initWithExrData(iw, ih, pixels, true);
            objALL->_imageData = pixels;
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;}
        case ADDOBJ:
            c++;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            addObj(objects[curOP->arg1]);
            
            if(init){
                objects[curOP->arg1]->objBace->release();
                objects[curOP->arg1]->objBace = nullptr;
                objects[curOP->arg1]->UV->release();
                objects[curOP->arg1]->UV = nullptr;
                if(objects[curOP->arg1]->tex){
                    objects[curOP->arg1]->tex->release();
                    objects[curOP->arg1]->tex = nullptr;
                }
            }
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;
        case REMOVEOBJ:{
            c++;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            objInfo *o = objects[curOP->arg1];
            bool isInit = false;
            if(o->tempRGB[0] != -1)
                isInit = true;
            
            removeObj(objects[curOP->arg1]);

            if(isInit){
                for(int i=0;i<3;i++){
                    o->rgb[i] = o->tempRGB[i];
                    o->tempRGB[i] = -1;
                }
            }
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;}
        case ADDLIGHT:{
            c++;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            //add one light
            
            addLight(lights[curOP->arg1]);

            if(init && lights[curOP->arg1]->baceTex){
                lights[curOP->arg1]->baceTex->release();
                lights[curOP->arg1]->baceTex = nullptr;
            }
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;}
        case REMOVELIGHT:
            c++;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            //remove one light
            removeLight(lights[curOP->arg1]);
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;
        case NORMALLIGHT:
            //now is modifying a light
            init = false;
            
            objALL->initWithExrData(originWidth, originHeight, objALL->_imageData, true);
            
            if(lightUpdated){
                light->initWithExrData(originWidth, originHeight, light->_imageData, true);
                lightUpdated = false;
            }
            
            showState->setUniformInt(STATE,2);
            showState->setUniformTexture(BACE,light);
            showState->setUniformTexture(LIGHT,curLight->baceTex);
            showState->setUniformTexture(ORIGINLIGHT,oLight);
            showState->setUniformTexture(OBJBACE,objALL);
            showState->setUniformVec4(COLOR,cocos2d::Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
            
          //  choose->setString(lights[curOP->arg1]->lightName);
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            loadSprite->setVisible(false);
            renderSprite->setVisible(false);
            loadPro->setVisible(false);
            proBG->setVisible(false);
            Helper::seekWidgetByName(uiLayout, "Panel_button")->setEnabled(true);
   //         this->removeChild(swallow);
            swallow->remove();
            
            csL->setValue(curLight->intensity);
            csR->setValue(curLight->rgb[0]);
            csG->setValue(curLight->rgb[1]);
            csB->setValue(curLight->rgb[2]);
            
            sL->setPercent(curLight->intensity*100);
            sR->setPercent(curLight->rgb[0]*100);
            sG->setPercent(curLight->rgb[1]*100);
            sB->setPercent(curLight->rgb[2]*100);
            
            stateColor->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            
            Helper::seekWidgetByName(uiLayout, "Image_name")->setVisible(true);
            showSprite->setVisible(true);
            
            break;
        case NORMALOBJ:
            init = false;
            
            objALL->initWithExrData(originWidth, originHeight, objALL->_imageData, true);
            
            if(lightCount > 0){
                if(curObj->tex){
                    showState->setUniformInt(STATE,1);
                    showState->setUniformTexture(TEX,curObj->tex);
                }
                else
                    showState->setUniformInt(STATE,0);
                
                if(lightUpdated){
                    light->initWithExrData(originWidth, originHeight, light->_imageData, true);
                    lightUpdated = false;
                }
                
                showState->setUniformTexture(LIGHT,light);
            }
            else{
                if(curObj->tex){
                    showState->setUniformInt(STATE,-1);
                    showState->setUniformTexture(TEX,curObj->tex);
                }
                else
                    showState->setUniformInt(STATE,-2);
            }
            showState->setUniformTexture(BACE,objALL);
            showState->setUniformTexture(ORIGIN,bace);
            showState->setUniformTexture(ORIGINLIGHT, oLight);
            showState->setUniformTexture(OBJUV,curObj->UV);
            showState->setUniformTexture(OBJBACE,curObj->objBace);
            showState->setUniformVec4(COLOR,cocos2d::Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1));
            
            stateColor->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
            stateR->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
            stateG->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
            stateB->setUniformVec3("rgb",cocos2d::Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
            
     //       choose->setString(objects[curOP->arg1]->objName);
            
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            loadSprite->setVisible(false);
            renderSprite->setVisible(false);
            loadPro->setVisible(false);
            proBG->setVisible(false);
            Helper::seekWidgetByName(uiLayout, "Panel_button")->setEnabled(true);
     //       this->removeChild(swallow);
            swallow->remove();
            
            sR->setPercent(curObj->rgb[0]*100);
            sG->setPercent(curObj->rgb[1]*100);
            sB->setPercent(curObj->rgb[2]*100);
            
            csR->setValue(curObj->rgb[0]);
            csG->setValue(curObj->rgb[1]);
            csB->setValue(curObj->rgb[2]);
    
            Helper::seekWidgetByName(uiLayout, "Image_name")->setVisible(true);
            showSprite->setVisible(true);
            
            break;
        case CLEAR:
            c = 1;
            init = true;
            loadPro->setPercentage(c/(float)totalProcess*100);
            
            float *data = (float*)malloc(spriteW*spriteH*sizeof(float)*4);
            memset(data, 0, spriteH*spriteW*sizeof(float)*4);
            
        //    float *ldata = (float*)malloc(originWidth*originHeight*sizeof(float)*4);
        //    memset(ldata, 0, originWidth*originHeight*sizeof(float)*4);
            
            light->initWithExrData(originWidth, originHeight, data, true);
            objALL->initWithExrData(spriteW, spriteH, data, true);
            bace->initWithExrData(spriteW, spriteH, data, true);
            objSingle->initWithExrData(spriteW, spriteH, data, true);
            
            light->_imageData = data;
            
          //  free(data);
           // free(ldata);
            
            lightUpdated = false;
            
            objSingle->_imageData = nullptr;
            
      /*      Sprite *ss = Sprite::createWithTexture(objSingle);
            ss->setScale(0.2);
            ss->setPosition(cocos2d::Vec2(100,700));
            this->addChild(ss,10);*/
            
    /*        Sprite* ss1 = Sprite::createWithTexture(light);
            ss1->setScale(0.2);
            ss1->setPosition(cocos2d::Vec2(100, 700));
            this->addChild(ss1,10);
            Sprite* ss2 = Sprite::createWithTexture(objALL);
            ss2->setScale(0.2);
            ss2->setPosition(cocos2d::Vec2(300, 700));
            this->addChild(ss2,10);
            Sprite* ss3 = Sprite::createWithTexture(bace);
            ss3->setScale(0.2);
            ss3->setPosition(cocos2d::Vec2(500, 700));
            this->addChild(ss3,10);*/
            
            showSprite->setVisible(false);
            loadSprite->setVisible(true);
                        
            old = curOP;
            curOP = curOP->next;
            if(!curOP)
                this->unscheduleUpdate();
            delete old;
            
            break;
	}
    
}
