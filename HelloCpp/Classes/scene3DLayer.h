//
//  scene3DLayer.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 13-11-6.
//
//

#ifndef __HelloCpp___scene3DLayer__
#define __HelloCpp___scene3DLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

#include "c3dToolKit.h"
class Cscene3DLayer : public CCLayer
{
public:
	Cscene3DLayer() {
        m_r=6;
        m_A=0;
        m_B=0;
        m_eyePos.init(0, 0, m_r, 1);
        m_eyeTg.init(0, 0, 0, 1);
        
        m_mosPos=CCPoint(0,0);
        m_mosPosf=CCPoint(0,0);
        
        m_scene=NULL;
        
    }
	virtual ~Cscene3DLayer(){
    };
    bool init();
public:
    //touch
	virtual void ccTouchesBegan(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
public:
    Cc3dVector4 m_eyePos;
    Cc3dVector4 m_eyeTg;
    float m_r;//distance from eyePos to eyeTg
    float m_A;//angle in XZ plane
    float m_B;//angle vertical
    void updateEyePos();
    
    CCPoint m_mosPos;
    CCPoint m_mosPosf;
    
    Cc3dScene*m_scene;
    vector<Cc3dSprite*> m_spriteList;

    
    
};

#endif /* defined(__HelloCpp___scene3DLayer__) */
