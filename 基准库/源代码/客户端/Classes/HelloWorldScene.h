#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoStudio.h"
#include "ui/CocosGUI.h"

#include "ReadExrImg.h"
#include "exrTexture.h"
#include "myRenderTexture.h"
#include "screenCapture.h"
#include "mySprite.h"
#include "SwallowLayer.h"

/*USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio;
using namespace ui;*/
using namespace IMF;

#define SCENEPATH "scenes/"
#define TEXTUREPATH "Textures/"
#define JSON "NewUi_1.json"

//texture2D
#define ORIGIN "u_origin"//origin bace
#define BACE "u_bace"
#define OBJBACE "u_objbace"
#define OBJUV "u_objuv"
#define LIGHT "u_light"
#define TEX "u_tex"
#define ORIGINLIGHT "u_originLight"
//vec4
#define COLOR "u_color"
//int
//-2 - object without texture and no light; -1 - object with texture and no light;
//0 - object without texture has light; 1 - object with texture has light; 2 - light; 3 - add an obejct to bace with texture;
//4 - remove an object from bace with texture; 5 - add a light to lightTex; 6 - remove a light in lightTex;
//7 - add an obejct to bace without texture; 8 - remove an obejct from bace without texture;
#define STATE "u_state"

//bace file name
#define BACEFILE "/bace.exr"

#define ORDER -50

struct objInfo{
	char *objName;
	char *baceFile;
	char *uvFile;
	float rgb[3];
	float tempRGB[3];
    float originRGB[3];
    exrTexture *objBace;
	exrTexture *UV;
	cocos2d::Texture2D *tex;
  //  cocos2d::Texture2D *originTex;
    std::string texName;
    std::string originTexName;
};

struct lightInfo{
	char *lightName;
	char *lightFile;
	float *bace;
	cocos2d::Texture2D *baceTex;
	float rgb[3];
	float intensity;
    float originRGB[3];
    float originIntensity;
};

class HelloWorld : public cocos2d::Layer
{
private:
	//tags
	int picTag;
    
	enum OPTYPE { INITBACE,INITOBJ,ADDLIGHT,REMOVELIGHT,ADDOBJ,REMOVEOBJ,NORMALOBJ,NORMALLIGHT,CLEAR,WAIT,GETOBJCOLOR,CHANGE,EMPTY };
    //	OPTYPE curOP;
    
	struct OPInfo{
		OPTYPE type;
		int arg1;
		int arg2;
		OPInfo *next;
	};
    
	//....
	bool testbool;//for test,will be delete after
    
    bool lightUpdated;
    
	OPInfo *curOP;//operate list
    
    int spriteX,spriteY,spriteW,spriteH;
    int originWidth,originHeight;
    
	cocos2d::GLProgramState* state;
	cocos2d::GLProgramState* stateR;
	cocos2d::GLProgramState* stateG;
	cocos2d::GLProgramState* stateB;
    cocos2d::GLProgramState* stateColor;
    
    int viewNum;
    int curViewNum;
    bool viewChanged;
    char **eyeViews,**viewNames;
	char * filepath;
	int objCount;
	int lightCount;
	objInfo **objects;
	lightInfo **lights;
    
  //  objInfo *oldObj,*newObj;
  //  lightInfo *oldLight,*newLight;
    
	objInfo *curObj;
	lightInfo *curLight;
    exrTexture *bace,*light,*objALL,*oLight,*shot, *objSingle;
    
	cocos2d::ui::Widget *uiLayout;
	int curView;
    cocos2d::ui::Widget *panels[5];
	cocos2d::ui::ImageView *i_color;
    cocos2d::ui::ScrollView *viewList;
    cocos2d::ui::ScrollView *objectList;
    cocos2d::ui::ScrollView *texList;
    
    cocos2d::ui::Slider *sR,*sG,*sB,*sL;
    cocos2d::extension::ControlSlider *csL,*csR,*csG,*csB;
    
    int sceneCount;
    char **sceneName;
    std::string sceneFile;
    std::string scenePath;
    std::string texturePath;
    
    Sprite *showSprite;
    Sprite *loadSprite;
    mySprite *renderSprite;
    cocos2d::GLProgramState* showState;
    ProgressTimer *loadPro;
    Sprite *proBG;
    
    SwallowLayer *swallow;
    
    int totalProcess;
    
  //  Label *choose;   // show the current object or light name
    Label *sceneDis;    //场景的描述文字
    
  //  cocostudio::Armature *armature;
    cocostudio::ActionObject *ani_ret;
    
    std::string sName,sIntro;
    bool loadingView;
    bool retPressed;
    bool playingAni;
    
//    std::string sceneTag;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(std::string tag, std::string name, std::string intro);
    
	void update(float dt);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(std::string tag, std::string name, std::string intro);
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
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
    bool getObjColor(objInfo *o);
    
	//load .exr texture
	exrTexture *loadTex(const char *path, bool inMem=false);
    
	//load user texture which is .png and .jpg
	cocos2d::Texture2D *loadUserTex(const char* path);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//use my shader
	void useShader(cocos2d::Sprite *sprite);
	void userShaderRGB(cocos2d::Sprite *sprite);
    
	//just for test
	void fortest(cocos2d::Object *sender,cocos2d::extension::Control::EventType controlEvent);
	void testmenu(cocos2d::Ref* pSender);
    
	//add filename to filepath, caller need free the return value after use
	char *getFilePath(const char *filename);
    
	//widget callback
	void bScene(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bObject(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bObjectActive(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bColor(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bTexture(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bLight(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bSave(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bView(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bViewActive(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bRedo(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
	void bFullScreen(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bFullScreenRet(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bSceneInfo(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bEditDone(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    void bReset(cocos2d::Object *sender,cocos2d::ui::TouchEventType eventType);
    
    void getSceneFiles();
    
    //slider callbacks
    void sliderR(Ref *sender,cocos2d::extension::Control::EventType event);
    void sliderG(Ref *sender,cocos2d::extension::Control::EventType event);
    void sliderB(Ref *sender,cocos2d::extension::Control::EventType event);
    void sliderL(Ref *sender,cocos2d::extension::Control::EventType event);
    
    //button callbacks
    void sceneItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event);
    void objectItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event);
    void texItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event);
    void viewItem(Ref *pSender,cocos2d::ui::Widget::TouchEventType event);
    
    void loadView(int num);
    void setAlphaAll(GLubyte value);
    
    //动画事件, animation callbacks
    void retAni();
    void objectEditAni();
    void emptyAni();
    
    // implement the "static create()" method manually
 //   CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
