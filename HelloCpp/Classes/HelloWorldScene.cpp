#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();//winSize equals to designResolutionSize
    
    //show frame rate info
    CCDirector::sharedDirector()->setDisplayStats(true);
    
    //scene3dLayer
    m_scene3DLayer=new Cscene3DLayer();
    m_scene3DLayer->autorelease();
    m_scene3DLayer->init();
    m_scene3DLayer->setAnchorPoint(ccp(0,0));
    m_scene3DLayer->setPosition(ccp(0,0));
    addChild(m_scene3DLayer,0);
    
    //demo name
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("3D ToolKit for cocos2d-x - Test 1", "Arial", 45);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height));
        this->addChild(pLabel, 1);
    }
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by Yang Chao (wantnon) 2014-1-5", "Arial", 25);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-60));
        this->addChild(pLabel, 1);
    }
    
    //controlButton_swithProjMode
    {
        CCScale9Sprite* btnUp=CCScale9Sprite::create("button.png");
        CCScale9Sprite* btnDn=CCScale9Sprite::create("button_dn.png");
        CCLabelTTF*title=CCLabelTTF::create("proj mode", "Helvetica", 30);
        CCControlButton* controlButton=CCControlButton::create(title, btnUp);
        controlButton->setBackgroundSpriteForState(btnDn,CCControlStateHighlighted);
        controlButton->setPreferredSize(CCSize(180,80));
        controlButton->setPosition(ccp(400,100));
        controlButton->addTargetWithActionForControlEvents(this, (SEL_CCControlHandler)(&HelloWorld::switchProjMode), CCControlEventTouchDown);
        this->addChild(controlButton);
        m_controlButton_swithProjMode=controlButton;

    }
    
    //controlButton_transform
    {
        CCScale9Sprite* btnUp=CCScale9Sprite::create("button.png");
        CCScale9Sprite* btnDn=CCScale9Sprite::create("button_dn.png");
        CCLabelTTF*title=CCLabelTTF::create("transform", "Helvetica", 30);
        CCControlButton* controlButton=CCControlButton::create(title, btnUp);
        controlButton->setBackgroundSpriteForState(btnDn,CCControlStateHighlighted);
        controlButton->setPreferredSize(CCSize(180,80));
        controlButton->setPosition(ccp(700,100));
        controlButton->addTargetWithActionForControlEvents(this, (SEL_CCControlHandler)(&HelloWorld::transform), CCControlEventTouchDown);
        this->addChild(controlButton);
        m_controlButton_transform=controlButton;

    }
    //projection mode label
    m_pLabel=CCLabelTTF::create("proj mode: Perspective", "Arial", 35);
    m_pLabel->setPosition(ccp(origin.x + visibleSize.width*(3.0/4),
                            origin.y + visibleSize.height - m_pLabel->getContentSize().height-100));
    this->addChild(m_pLabel, 1);

    
   /* // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite,-1);
	*/
    return true;
}

void HelloWorld::switchProjMode(CCObject *senderz, cocos2d::extension::CCControlEvent controlEvent){
    Cc3dCamera*camera=this->m_scene3DLayer->m_scene->getCamera3D();
    switch(camera->getProjectionMode())
    {
        case ec3dPerspectiveMode:{
            camera->setProjectionMode(ec3dOrthographicMode);
            m_pLabel->setString("proj mode: Orthographic");
        }break;
        case ec3dOrthographicMode:{
            camera->setProjectionMode(ec3dPerspectiveMode);
            m_pLabel->setString("proj mode: Perspective");
        }break;
        
    }
}
void HelloWorld::transform(CCObject *senderz, CCControlEvent controlEvent){
    if(isScheduleOn){
        //restore inital matrix
        vector<Cc3dSprite*> spriteList=this->m_scene3DLayer->m_spriteList;
        int nSprite=(int)spriteList.size();
        for(int i=0;i<nSprite;i++){
            spriteList[i]->setTransform3D(initalMatList[i]);
        }
        //stop update
        unscheduleUpdate();
        isScheduleOn=false;
        
    }else{
        //store inital matrix
        initalMatList.clear();
        vector<Cc3dSprite*> spriteList=this->m_scene3DLayer->m_spriteList;
        int nSprite=(int)spriteList.size();
        for(int i=0;i<nSprite;i++){
            initalMatList.push_back(spriteList[i]->getTransform3D());
        }
        //start update
        scheduleUpdate();
        isScheduleOn=true;
    }
}
void HelloWorld::update(float t){
    vector<Cc3dSprite*> spriteList=this->m_scene3DLayer->m_spriteList;
    spriteList[0]->rotateRelativeToParent3D(cc3dv4(0, 1, 0, 0), 3);
    spriteList[0]->rotate3D(cc3dv4(1, 0, 0, 0), 3);
    spriteList[2]->rotateRelativeToParent3D(cc3dv4(0, 1, 0, 0), 3);
    spriteList[2]->rotate3D(cc3dv4(0, 1, 0, 0), 6);
    
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
