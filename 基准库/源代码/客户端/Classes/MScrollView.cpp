#include "MScrollView.h"

#include "MeijiaMainScene.h"
#include "SearchDlg.h"

CCScene* MScrollView::scene()
{
    CCScene *scene = CCScene::create();
    
    MScrollView *layer = MScrollView::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MScrollView::init()
{
    CCLayer::init();
    sceneNum = SCENESUM;
    
    layertest = nullptr;
    
    for(int i=0; i<sceneNum; i++)
    {
        intromap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "intro\nintro\nintro\nintro\n"));
        snamemap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "TITLE"));
        mdatemap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "date"));
        designermap.insert(pair<string, string>("0b7587a9-940c-4965-9cbc-45c3a1380ae5", "designer"));
    }
    
    // ************ ¥•√˛ÕÃ … ************
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MScrollView::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MScrollView::onTouchEnded, this);
   
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void MScrollView::initScrollView(const int _sceneNum, std::vector<std::string>& _sceneID)
{
    sceneNum	= _sceneNum;
    sceneID		= _sceneID;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint center = ccp(winSize.width / 2, winSize.height / 2);
    
    //¥¥Ω®“ª∏ˆΩ·µ„
    CCNode* c = CCNode::create();
    
    int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);
    for(int i = 0; i < (int)(sceneNum / 6); i++)
    {
        Sprite* sprite = Sprite::create("voidBg.png");
        //sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);
        
        //…Ë÷√Õº∆¨µƒŒª÷√£¨√ø¡Ω’≈Õº∆¨œ‡≤Ó“ª∏ˆ∆¡ƒªµƒøÌ∂»
        sprite->setPosition(ccpAdd(center, ccp(i*winSize.width, 0)));
        addSceneBorder(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
        addScenePic(sprite, ITEMROWS, ITEMCOLS, i, ITEMCOLS * ITEMROWS);
        
        //∏¯ ”Õº±‡∫≈
        char buf[10];
        sprintf(buf, "%d/%d", i + 1, sumpage);
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36);
        label->setString(buf);
        label->setColor(ccc3(66, 66, 66));
        sprite->addChild(label);
        label->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 12));
    }
    
    // ∑¿÷π≥ˆœ÷◊Ó∫Û“ª“≥ÃÓ≤ª¬˙
    if(sceneNum - sceneNum/6*6 > 0){
        Sprite* sprite = Sprite::create("voidBg.png");
        //sprite->setAnchorPoint(Vec2(0, 0));
        c->addChild(sprite);
        
        //…Ë÷√Õº∆¨µƒŒª÷√£¨√ø¡Ω’≈Õº∆¨œ‡≤Ó“ª∏ˆ∆¡ƒªµƒøÌ∂»
        sprite->setPosition(ccpAdd(center, ccp(sceneNum/6 * winSize.width, 0)));
        addSceneBorder(sprite, ITEMROWS, ITEMCOLS, sceneNum/6, sceneNum - sceneNum/6*6);
        addScenePic(sprite, ITEMROWS, ITEMCOLS,sceneNum/6, sceneNum - sceneNum/6*6);
        
        //∏¯ ”Õº±‡∫≈
        char buf[10];
        sprintf(buf, "%d/%d", sceneNum/6 + 1, (int)(sceneNum / 6 + 1));
        LabelTTF* label = LabelTTF::create(buf, "Arial", 36);
        label->setString(buf);
        sprite->addChild(label);
        label->setColor(ccc3(66, 66, 66));
        label->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 12));
    }
    
    //πˆ∂Ø ”Õº
    //µ⁄“ª∏ˆ≤Œ ˝£∫‘⁄¥∞ø⁄œ‘ æµƒ ”Õº¥Û–°
    //µ⁄∂˛∏ˆ≤Œ ˝£∫Ω·µ„CCNode
    //view = ScrollView::create(winSize, c);
    c->setContentSize(CCSizeMake(sumpage* winSize.width, winSize.height));
    _contaner = c;
    
    view = ScrollView::create(CCSizeMake(1024, 768), c);
    view->setContentOffset(CCPointZero);
    //…Ë÷√ ”Õº‘À∂Øµƒ∑ΩœÚŒ™ÀÆ∆Ω‘À∂Ø
    view->setDirection(ScrollView::Direction::HORIZONTAL);
    view->setPosition(CCPointZero);
    this->addChild(view);
    
    //…Ë÷√ ”ÕºµƒøÌ∂»∫Õ∏ﬂ∂»
    if(sceneNum % 6 == 0)
    {
        view->setContentSize(Size(winSize.width * (int)(sceneNum / 6), winSize.height));
    }
    else
    {
        view->setContentSize(Size(winSize.width * (int)(sceneNum / 6 + 1), winSize.height));
    }
    
    //»°œ˚ScrollViewµƒµØ–‘
    view->setBounceable(false);
    
    //◊¢≤·¥•√˛ ¬º˛
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
}

void MScrollView::setScrollInfo(
                                std::map<std::string, std::string>& _snamemap,
                                std::map<std::string, std::string>& _intromap,
                                std::map<std::string, std::string>& _designermap,
                                std::map<std::string, std::string>& _mdatemap)
{
    intromap.clear();
    snamemap.clear();
    designermap.clear();
    mdatemap.clear();
    
    intromap = _intromap;
    snamemap = _snamemap;
    designermap = _designermap;
    mdatemap = _mdatemap;
    return;
}

// Û±Íµ„œ¬µƒ ±∫Ú
bool MScrollView::onTouchBegan(Touch* touch, Event* event)
{
    //µ√µΩ Û±Íµ„œ¬»•µƒ ±∫ÚµƒŒª÷√
    ptDown = touch->getStartLocation();
    return true;
}

//void MScrollView::onTouchMoved(Touch* touch, Event* event)
//{
//	//µ√µΩ Û±Íµ„œ¬»•µƒ ±∫ÚµƒŒª÷√
//    ptDown = touch->getStartLocation();
//    // return true;
//}

// Û±Í∆¿¥µƒ ±∫Ú
void MScrollView::onTouchEnded(Touch* touch, Event* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    ////µ√µΩ Û±Íµ„œ¬»•µƒ ±∫ÚµƒŒª÷√
    //Point ptDown = touch->getStartLocation();
    
    //µ√µΩ Û±ÍÀ…ø™ ±µƒŒª÷√
    Point ptUp = touch->getLocation();
    
    //µ±¡Ω∏ˆŒª÷√µƒæ‡¿Îµƒ∆Ω∑Ω–°”⁄25 ±(»œŒ™ «µ„ª˜£¨∑Ò‘Ú «ª¨∂Ø)
    if(pow(ptUp.x - ptDown.x, 2) >= 16)
    {
        //ª¨∂Ø
        int x = _contaner->getPositionX();
        int sumpage = (sceneNum%6 == 0)? (int)(sceneNum / 6) : (int)(sceneNum / 6 + 1);
        
        if (x >= -(sumpage-1) * winSize.width && x <= 0)
        {
            // adjust
            // 0, -1024, -2048, -3072, -4096
            //int idx = (-x + winSize.width/2)/ winSize.width;
            int idx = (-x + 512) / 1024;
            //x = -idx * winSize.width;
            x = -idx * 1024;
        }
        else if(x >=0)
        {
            x = 0;
        }
        else
        {
            x = -(sumpage-1) * winSize.width;
        }
        
        MoveTo* moveTo = MoveTo::create(0.001f, ccp(x, this->_contaner->getPositionY()));
        this->_contaner->runAction(moveTo);
        view->setContentOffsetInDuration(cocos2d::Vec2(x, this->_contaner->getPositionY()), 0.001f);
        
        //if(ptUp.x - ptDown.x > 0)
        //{
        //	if(x >= 0) x = 0;
        //	if(x <= )
        //	MoveTo* moveTo = MoveTo::create(0.001f, ccp(x, this->_contaner->getPositionY()));
        //          this->_contaner->runAction(moveTo);
        //}
    }
}

void MScrollView::addSceneBorder(Sprite* sprite, int itemrows, int itemcols, int page, int itemnum)
{
    menu = Menu::create();
    int index = 0;
    int num = 0;
    index += page * 6;
    for(int i=0; i<itemrows; i++)
        for(int j=0; j<itemcols; j++)
        {
            sceneBorder[num] = MenuItemImage::create(
                                                       "BorderNormal.png",
                                                       "BorderSelected.png",
                                                       //CC_CALLBACK_2(MScrollView::sceneBorderCallback, this, index, menu));
                                                       CC_CALLBACK_1(MScrollView::sceneBorderCallback, this, index, menu));
            sceneBorder[num]->setScale(0.9f);
            sceneBorder[num]->setPosition(cocos2d::Vec2( sprite->getContentSize().width/(itemcols+1)*(j+1),
                                                 sprite->getContentSize().height - sprite->getContentSize().height/(itemrows+1)*(i+1) ));
            
            // ∑¿÷π◊Ó∫Û“ª“≥≤ªπª∑≈¬˙ 6 ∏ˆ
            if(num+1 > itemnum) continue;
            menu->addChild(sceneBorder[num], 1);
            
            num++;
            index++;
        }
    
    //menu->setPosition(sprite->getContentSize().width/2, sprite->getContentSize().height/2);
    menu->setPosition(cocos2d::Vec2(0, 0));
    sprite->addChild(menu);
    
    //// ‘§¡ÙΩ”ø⁄‘⁄±ﬂøÚƒ⁄ÃÌº”Œƒ◊÷°¢Àı¬‘Õºµ»
    //auto label = LabelTTF::create("meijia", "Arial", 80);
    //label->setPosition(Vec2(sceneItem[0]->getPosition().x, sceneItem[0]->getPosition().y));
    //menu->addChild(label, 0);
    return;
}

void MScrollView::addScenePic(Sprite* sprite, int itemrows, int itemcols, int page, int itemnum)
{
    int index = 0;
    index += page * 6;
    int num = 0;
    if(num+1 <= itemnum){
        scenePic[0] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    if(num+1 <= itemnum){
        scenePic[1] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    if(num+1 <= itemnum){
        scenePic[2] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    if(num+1 <= itemnum){
        scenePic[3] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    if(num+1 <= itemnum){
        scenePic[4] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    if(num+1 <= itemnum){
        scenePic[5] = Sprite::create("thumbs/" + sceneID[index] + ".png");
        num++;
        index++;
    }
    
    for(int i=0; i<itemrows; i++)
        for(int j=0; j<itemcols; j++)
        {
            index = i*itemcols + j;
            // ∑¿÷π◊Ó∫Û“ª“≥≤ªπª∑≈¬˙ 6 ∏ˆ
            if(index+1 > itemnum) return;
            
            scenePic[index]->setPosition(sceneBorder[index]->getPosition().x, sceneBorder[index]->getPosition().y);
            
            sprite->addChild(scenePic[index], 0);
        }
    
    return;
}

void MScrollView::onEnter(){
    Layer::onEnter();
    if(layertest)
    {
        CCLog("enter\n");
        _eventDispatcher->removeEventListener(layertest->listener);
        this->removeChild(layertest);
    }
}

void MScrollView::sceneBorderCallback(cocos2d::Ref* pSender, int id, cocos2d::Menu* menu)
{
    layertest = ConfirmDlg::create();
    std::string _dlgID;
    
    //// ***** new *****
    layertest->setID(sceneID[id]);
    //layertest->initLabel(intro, titlestr);
    layertest->initLabel(intromap[sceneID[id]] + "\n" + mdatemap[sceneID[id]], snamemap[sceneID[id]]);
    
    layertest->setOutMenu(outMenu);
    this->addChild(layertest, 10);
    return;
}

void MScrollView::setOutMenu(cocos2d::Menu* _outMenu)
{
    outMenu = _outMenu;
}