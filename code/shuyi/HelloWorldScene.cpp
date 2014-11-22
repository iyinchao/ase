#include "HelloWorldScene.h"
//#include "MySprite.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//set tags
	picTag = 200;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	Texture2D *ltex = loadTex("D:\\p1.jpg");
    auto sprite = Sprite::createWithTexture(ltex);
	//sprite->setScale(1.2);
    // position the sprite on the center of the screen
	sprite->setPosition(Vec2(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
	sprite->setTag(200);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	useShader(sprite);

	state = GLProgramState::getOrCreateWithGLProgram(sprite->getShaderProgram());	

	Sprite *picture = (Sprite*)this->getChildByTag(picTag);
	//myRTT = RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	//myRTT1 = RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	//myRTT2 = RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	//myRTT3 = RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	myRTT = (myRenderTexture*)RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	myRTT1 = (myRenderTexture*)RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	myRTT2 = (myRenderTexture*)RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	myRTT3 = (myRenderTexture*)RenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);
	
	//myRTT4 = myRenderTexture::create(picture->getContentSize().width,picture->getContentSize().height);

	light = myRTT1->getSprite()->getTexture();
	objALL = myRTT2->getSprite()->getTexture();
	bace = myRTT3->getSprite()->getTexture();

	getTexFileName("D:\\ts1_data\\content.txt");

	myRTT->getSprite()->setPosition(Vec2(picture->getContentSize().width/2,picture->getContentSize().height/2));
	myRTT1->getSprite()->setPosition(Vec2(picture->getContentSize().width/2,picture->getContentSize().height/2));
	
	this->addChild(myRTT,20);
	//this->addChild(myRTT->getSprite(),-20);

	//myRTT1->getSprite()->setPosition(Vec2(580,300));
	this->addChild(myRTT1,100);
	//this->addChild(myRTT1->getSprite(),-10);

	myRTT2->getSprite()->setPosition(Vec2(580,300));
	this->addChild(myRTT2,-5);
	//this->addChild(myRTT2->getSprite(),-5);

	myRTT3->getSprite()->setPosition(Vec2(580,300));
	this->addChild(myRTT3,-15);
	//this->addChild(myRTT3->getSprite(),15);

	curLight = nullptr;
	curObj = nullptr;

	curOP = nullptr;

	oldLight = nullptr;
    oldObj = nullptr;
    newLight = nullptr;
    newObj = nullptr;

	//load ui json file
	uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("NewUi_1.json");
	this->addChild(uiLayout,-1);

	views[0] = "Panel_Object";
	views[1] = "Panel_color";
	views[2] = "Scroll_Texture";
	curView = 0;
	Helper::seekWidgetByName(uiLayout, views[0])->setVisible(true);
	Helper::seekWidgetByName(uiLayout, views[1])->setVisible(false);
	Helper::seekWidgetByName(uiLayout, views[2])->setVisible(false);

	//set buttons
	auto b_color = (Button*)Helper::seekWidgetByName(uiLayout, "Button_color");
	b_color->addTouchEventListener(this,toucheventselector(HelloWorld::bColor));
	auto b_scene = (Button*)Helper::seekWidgetByName(uiLayout,"Button_scene");
	b_scene->addTouchEventListener(this,toucheventselector(HelloWorld::bScene));
	auto b_object = (Button*)Helper::seekWidgetByName(uiLayout,"Button_object");
	b_object->addTouchEventListener(this,toucheventselector(HelloWorld::bObject));
	auto b_texture = (Button*)Helper::seekWidgetByName(uiLayout,"Button_texture");
	b_texture->addTouchEventListener(this,toucheventselector(HelloWorld::bTexture));
	auto b_undo = (Button*)Helper::seekWidgetByName(uiLayout,"Button_undo");
	b_undo->addTouchEventListener(this,toucheventselector(HelloWorld::bUndo));
	auto b_redo = (Button*)Helper::seekWidgetByName(uiLayout,"Button_redo");
	b_redo->addTouchEventListener(this,toucheventselector(HelloWorld::bRedo));
	auto b_save = (Button*)Helper::seekWidgetByName(uiLayout,"Button_save");
	b_save->addTouchEventListener(this,toucheventselector(HelloWorld::bSave));
	auto b_fullscreen = (Button*)Helper::seekWidgetByName(uiLayout,"Button_fullscreen");
	b_fullscreen->addTouchEventListener(this,toucheventselector(HelloWorld::bFullScreen));

    return true;
}

void HelloWorld::sliderR(Ref *sender,SliderEventType type){
	auto slider = (Slider*)sender;
	if(curObj){
        if(oldObj)
            free(oldObj);
        
        oldObj = (objInfo*)malloc(sizeof(objInfo));
        memcpy(oldObj, curObj, sizeof(objInfo));
        
		curObj->rgb[0] = slider->getPercent()/100.0;
		state->setUniformVec4(COLOR,Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
            if(oldLight)
                free(oldLight);
            
            oldLight = (lightInfo*)malloc(sizeof(lightInfo));
            memcpy(oldLight, curLight, sizeof(lightInfo));
            
			curLight->rgb[0] = slider->getPercent()/100.0;
			state->setUniformVec4(COLOR,Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateG->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateB->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderG(Ref *sender,SliderEventType type){
	auto slider = (Slider*)sender;
	if(curObj){
		curObj->rgb[1] = slider->getPercent()/100.0;
		state->setUniformVec4(COLOR,Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateB->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
			curLight->rgb[1] = slider->getPercent()/100.0;
			state->setUniformVec4(COLOR,Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateR->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateB->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderB(Ref *sender,SliderEventType type){
	auto slider = (Slider*)sender;
	if(curObj){
		curObj->rgb[2] = slider->getPercent()/100.0;
		state->setUniformVec4(COLOR,Vec4(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2],1.0));
		stateColor->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateR->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
        stateG->setUniformVec3("rgb",Vec3(curObj->rgb[0],curObj->rgb[1],curObj->rgb[2]));
		return;
	}
	else{
		if(curLight){
			curLight->rgb[2] = slider->getPercent()/100.0;
			state->setUniformVec4(COLOR,Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
			stateColor->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateR->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
            stateG->setUniformVec3("rgb",Vec3(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2]));
		}
	}
}

void HelloWorld::sliderL(Ref *sender,SliderEventType type){
	auto slider = (Slider*)sender;
	if(curObj){
		return;
	}
	else{
		if(curLight){
			curLight->intensity = slider->getPercent()/100.0;
			state->setUniformVec4(COLOR,Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
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
	end = strrchr(begin,'\\');
	int length = end-begin+1;
	filepath = (char*)malloc(length+1);
	memcpy(filepath,begin,length);
	*(filepath+length) = 0;

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
		objects[i]->rgb[0] = 1.0;
		begin = end+1;
		end = strchr(begin,' ');
		*end = 0;
		objects[i]->tempRGB[1] = atoi(begin)/255.0;
		objects[i]->rgb[1] = 1.0;
		begin = end+1;
		end = strchr(begin,')');
		*end = 0;
		objects[i]->tempRGB[2] = atoi(begin)/255.0;
		objects[i]->rgb[2] = 1.0;
        
		end = end+1;
        
        //object texture
		begin = end+2;
		end = strchr(begin,'\r');
		*end = 0;
		if(strcmp(begin,"0")){
			objects[i]->tex = loadUserTex(begin);
            objects[i]->texName = begin;
		}
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
		lights[0]->lightFile = "bace.png";
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
		begin = end+1;
		end = strchr(begin,' ');
		*end = 0;
		lights[i]->rgb[1] = atoi(begin)/255.0;
		begin = end+1;
		end = strchr(begin,')');
		*end = 0;
		lights[i]->rgb[2] = 1.0;
        
		begin = end+2;
		end = strchr(begin,'\r');
		*end = 0;
		lights[i]->intensity = atoi(begin)/100.0;
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

//load .exr texture
Texture2D * HelloWorld::loadTex(const char *path){
	return Director::getInstance()->getTextureCache()->addImage(path);
}

//load user texture which is .png and .jpg
Texture2D *HelloWorld::loadUserTex(const char* filename){
	std::string fullpath = filename;
	fullpath = TEXTUREPATH+fullpath;
	return Director::getInstance()->getTextureCache()->addImage(fullpath);
}

bool HelloWorld::initTexture(){

	//gen RTT texture

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
			temp->type = REMOVEOBJ;
			temp->arg1 = i;
			temp->next = curOP;
			curOP = temp;
		}

		temp = new OPInfo;
		temp->type = INIT;
		temp->next = curOP;
		curOP = temp;
	}

	//init light
	if(lightCount > 0){
		for(int i=0;i<lightCount;i++){
			temp = new OPInfo;
			temp->type = ADDLIGHT;
			temp->arg1 = i;
			temp->next = curOP;
			curOP = temp;
		}
	}
	else{
		temp = new OPInfo;
		temp->type = ADDLIGHT;
		temp->arg1 = 0;
		temp->next = curOP;
		curOP = temp;
	}

	temp = new OPInfo;
	temp->type = CLEAR;
	temp->next = curOP;
	curOP = temp;

	//objects[0]->tex = Director::getInstance()->getTextureCache()->addImage("s2.png");

	return true;
}

//add light l to lightTex
bool HelloWorld::addLight(lightInfo *l){
	if(!l)
		return false;
    
	if(!l->bace){
		char *temp = getFilePath(l->lightFile);
		l->bace = loadTex(temp);
		free(temp);
		if(l->bace == NULL)
			return false;
	}
    
	state->setUniformInt(STATE,5);
	state->setUniformTexture(LIGHT,l->bace);
	state->setUniformTexture(BACE,light);
	state->setUniformVec4(COLOR,Vec4(l->rgb[0],l->rgb[1],l->rgb[2],l->intensity));
    
	//Sprite *p = (Sprite*)this->getChildByTag(picTag);
	//myRTT->beginWithClear(0,0,0,0);
	//p->visit();
	//myRTT->end();
    
	return true;
}

//remove light l from lightTex
bool HelloWorld::removeLight(lightInfo *l){
	if(!l)
		return false;
    
	if(!l->bace){
		char *temp = getFilePath(l->lightFile);
		l->bace = loadTex(temp);
		free(temp);
		if(l->bace == NULL)
			return false;
	}
    
	state->setUniformInt(STATE,6);
	state->setUniformTexture(LIGHT,l->bace);
	state->setUniformTexture(BACE,light);
	state->setUniformVec4(COLOR,Vec4(l->rgb[0],l->rgb[1],l->rgb[2],l->intensity));
	
	Sprite *p = (Sprite*)this->getChildByTag(picTag);
	myRTT->beginWithClear(0,0,0,0);
	p->visit();
	myRTT->end();
    
	return true;
}

//for modifying light intensity.
//remove target light from lightmap and change shader state
bool HelloWorld::setCurLight(int lightNum){
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

	temp = new OPInfo;
	temp->next = curOP;
	temp->type = REMOVELIGHT;
	temp->arg1 = lightNum;
	curOP = temp;

	if(num != -1){
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDLIGHT;
		temp->arg1 = num;
		curOP = temp;
	}

	if(num2 != -1){
		temp = new OPInfo;
		temp->next = curOP;
		temp->type = ADDOBJ;
		temp->arg1 = num2;
		curOP = temp;
	}

	return true;
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
	} 
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

//not complete
void HelloWorld::bScene(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
}

//not complete
void HelloWorld::bObject(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
    if(curView != 0)
		Helper::seekWidgetByName(uiLayout,views[curView])->setVisible(false);
    
	auto *w = (Widget*)Helper::seekWidgetByName(uiLayout,views[0]);
	w->setVisible(true);
    
	curView = 0;
}

//not complete
void HelloWorld::bColor(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
	if(curView != 1)
		Helper::seekWidgetByName(uiLayout,views[curView])->setVisible(false);
    
	auto *w = (Widget*)Helper::seekWidgetByName(uiLayout,views[1]);
	w->setVisible(true);
        
	curView = 1;
}

//not complete
void HelloWorld::bTexture(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
    
	if(curView != 2)
		Helper::seekWidgetByName(uiLayout,views[curView])->setVisible(false);
    
	auto w = (Widget*)Helper::seekWidgetByName(uiLayout,views[2]);
	w->setVisible(true);
    
	curView = 2;
}

//not complete
void HelloWorld::bSave(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;

}

//not complete
void HelloWorld::bUndo(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;
}

//not complete
void HelloWorld::bRedo(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;

}

//not complete
void HelloWorld::bFullScreen(Object *sender,TouchEventType eventType){
	if(eventType != TouchEventType::TOUCH_EVENT_ENDED)
		return;

}

void HelloWorld::update(float dt){
	this->unscheduleUpdate();

	if(!curOP){
        this->unscheduleUpdate();
		return;
	}

	OPInfo *old;
	Image *img;
	Sprite *p = (Sprite*)this->getChildByTag(picTag);
	switch(curOP->type){
        case INIT:{
            //set objALL to bace
            myRTT3->beginWithClear(0,0,0,0);
			p->visit();
            //myRTT->getSprite()->visit();
            myRTT3->end();
			img = myRTT3->newImage();
			img->saveToFile("E:\\ppp\\init_bace.png");
			bace->initWithImage(img);

            myRTT2->beginWithClear(0,0,0,0);
            p->visit();
            //myRTT->getSprite()->visit();
            myRTT2->end();
			img = myRTT2->newImage();
			img->saveToFile("E:\\ppp\\init_objall.png");
			objALL->initWithImage(img);
            
            old = curOP;
            curOP = curOP->next;
            delete old;
            
            break;}
        case ADDLIGHT:
            //add one light
            addLight(lights[curOP->arg1]);

            myRTT1->begin();
            p->visit();
            //myRTT->getSprite()->visit();
            myRTT1->end();
			img = myRTT1->newImage();
			img->saveToFile("E:\\ppp\\addlight_light.png");
			light->initWithImage(img);
            
            old = curOP;
            curOP = curOP->next;
            delete old;
            
            break;
        case REMOVELIGHT:
            //remove one light
            removeLight(lights[curOP->arg1]);

            myRTT1->begin();
            p->visit();
            //myRTT->getSprite()->visit();
            myRTT1->end();
			light->initWithImage(myRTT1->newImage());
            
            old = curOP;
            curOP = curOP->next;
            delete old;
            
            break;
        case NORMALLIGHT:
            //now is modifying a light
            
            state->setUniformInt(STATE,2);
            state->setUniformTexture(BACE,light);
            state->setUniformTexture(LIGHT,curLight->bace);
            state->setUniformTexture(ORIGIN,bace);
            state->setUniformTexture(OBJBACE,objALL);
            state->setUniformVec4(COLOR,Vec4(curLight->rgb[0],curLight->rgb[1],curLight->rgb[2],curLight->intensity));
            
            old = curOP;
            curOP = curOP->next;
            delete old;
            
            //loadSprite->setVisible(false);
            
            break;
        case CLEAR:
            myRTT1->beginWithClear(0,0,0,0);
            myRTT1->end();
            
            old = curOP;
            curOP = curOP->next;
            delete old;
            
            break;
	}
    
}