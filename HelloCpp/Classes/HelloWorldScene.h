#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "scene3DLayer.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
public:
    HelloWorld(){
        m_scene3DLayer=NULL;
        isScheduleOn=false;
        m_pLabel=NULL;
    }
    virtual ~HelloWorld(){
    
    }
    void visit();
    void update(float t);
public:
    //3D scene layer
    Cscene3DLayer*m_scene3DLayer;
    
    //controlButton and its callback
    CCControlButton* m_controlButton_swithProjMode;
    void switchProjMode(CCObject *senderz, CCControlEvent controlEvent);
    CCControlButton* m_controlButton_transform;
    void transform(CCObject *senderz, CCControlEvent controlEvent);
    
    //label show current projection mode
    CCLabelTTF* m_pLabel;
    
    //store initial transform matrixs of 3D sprites in scene3DLayer (used for restore)
    vector<Cc3dMatrix4> initalMatList;
    
    //flag to mark whether schedule update is running
    bool isScheduleOn;
    
    

};

#endif // __HELLOWORLD_SCENE_H__
