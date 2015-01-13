#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <opencv2/opencv.hpp>
#include "cocos-ext.h"
#include "myRenderTexture.h"
#include "CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio;
using namespace ui;

//texture2D
#define ORIGIN "u_origin"//origin bace
#define BACE "u_bace"
#define OBJBACE "u_objbace"
#define OBJUV "u_objuv"
#define LIGHT "u_light"
#define TEX "u_tex"
#define CURBACE "u_curbace"
//vec4
#define COLOR "u_color"
//int
//-2 - object without texture and no light; -1 - object with texture and no light;
//0 - object without texture has light; 1 - object with texture has light; 2 - light; 3 - add an obejct to bace with texture;
//4 - remove an object from bace with texture; 5 - add a light to lightTex; 6 - remove a light in lightTex;
//7 - add an obejct to bace without texture; 8 - remove an obejct from bace without texture;
#define STATE "u_state"

//bace file name
#define BACEEXR "bace.exr"

#define SCENEPATH "/Users/labda/Desktop/scenes/"
#define TEXTUREPATH "Textures\\"

struct objInfo{
	char *objName;
	char *baceFile;
	char *uvFile;
	float rgb[3];
	float tempRGB[3];
    cocos2d::Texture2D *objBace;
	cocos2d::Texture2D *UV;
	cocos2d::Texture2D *tex;
    std::string texName;
};

struct lightInfo{
	char *lightName;
	char *lightFile;
	cocos2d::Texture2D *bace;
	cocos2d::Texture2D *tex;
	float rgb[3];
	float intensity;
};

class HelloWorld : public cocos2d::Layer
{
private:
	//tags
	int picTag;

	enum OPTYPE { INIT,ADDLIGHT,REMOVELIGHT,ADDOBJ,REMOVEOBJ,NORMALOBJ,NORMALLIGHT,CLEAR,BACELIGHT };
//	OPTYPE curOP;

	struct OPInfo{
		OPTYPE type;
		int count;
		int arg1;
		OPInfo *next;
	};

	//....
	bool testbool;//for test,will be delete after

	OPInfo *curOP;//operate list

	cocos2d::GLProgramState* state;
	cocos2d::GLProgramState* stateR;
	cocos2d::GLProgramState* stateG;
	cocos2d::GLProgramState* stateB;
    cocos2d::GLProgramState* stateColor;

	char * filepath;
	int objCount;
	int lightCount;
	objInfo **objects;
	lightInfo **lights;

	objInfo *oldObj,*newObj;
    lightInfo *oldLight,*newLight;

	objInfo *curObj;
	lightInfo *curLight;
	Texture2D *bace;//bace texture for origin light
	Texture2D *light;//RTT texture for all lights
	Texture2D *objALL;//RTT texture for all objects without light
	Texture2D *lightRTT;//RTT texture for lights except one of them
	Texture2D *objExceptOne;//RTT texture for objects except one of them without light
	myRenderTexture *myRTT;
	myRenderTexture *myRTT1;//for light
	myRenderTexture *myRTT2;//for objALL
	myRenderTexture *myRTT3;//for bace
	myRenderTexture *myRTT4;//for objExceptOne

	cocos2d::ui::Widget *uiLayout;
	int curView;
    std::string views[3];
	cocos2d::ui::ImageView *i_color;
    cocos2d::ui::ListView *sceneList;
    cocos2d::ui::ListView *objectList;
    
    cocos2d::ui::Slider *sR,*sG,*sB,*sL;


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	void update(float dt);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	//init, gen all needed texture
	bool initTexture();

	//read contentfile and get objects and lights, their names are stored in objFiles and lightFiles
	bool getTexFileName(const char* contentfile);

	//set current object to obj and set shader uniform
	bool setCurObj(int objNum);
	bool setCurLight(int lightNum);

	//RTT
	bool addLight(lightInfo *l);
	bool removeLight(lightInfo *l);
	bool addObj(objInfo *o);
	bool removeObj(objInfo *o);

	//load .exr texture
	Texture2D *loadTex(const char *path);

	//load user texture which is .png and .jpg
	Texture2D *loadUserTex(const char* path);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//use my shader
	void useShader(cocos2d::Sprite *sprite);
	void userShaderRGB(Sprite *sprite);

	//just for test
	void fortest(Object *sender,Control::EventType controlEvent);
	void testmenu(cocos2d::Ref* pSender);

	//add filename to filepath, caller need free the return value after use
	char *getFilePath(const char *filename);

	//widget callback
	void bScene(Object *sender,TouchEventType eventType);
	void bObject(Object *sender,TouchEventType eventType);
	void bColor(Object *sender,TouchEventType eventType);
	void bTexture(Object *sender,TouchEventType eventType);
	void bSave(Object *sender,TouchEventType eventType);
	void bUndo(Object *sender,TouchEventType eventType);
	void bRedo(Object *sender,TouchEventType eventType);
	void bFullScreen(Object *sender,TouchEventType eventType);

	void sliderR(Ref *sender,cocos2d::ui::SliderEventType type);
    void sliderG(Ref *sender,cocos2d::ui::SliderEventType type);
    void sliderB(Ref *sender,cocos2d::ui::SliderEventType type);
    void sliderL(Ref *sender,cocos2d::ui::SliderEventType type);

	void texItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
