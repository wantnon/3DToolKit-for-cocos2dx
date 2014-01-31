//
//  c3dCamera.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-7.
//
//

#ifndef __HelloCpp__c3dCamera__
#define __HelloCpp__c3dCamera__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dVector.h"
#include "c3dMatrix.h"
#include "c3dGLMath.h"
#include "c3dCommonFunc.h"
#include "c3dValueCache.h"
#include "c3dMatrixStackInfoGetor.h"
#include "c3dRange.h"
class Cc3dCamera:public CCCamera
{
public:
    Cc3dCamera(){
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        m_fovy=60;
        m_aspect=winSize.width/winSize.height;
        m_zNear=0.5;
        m_zFar=1500;
        
        const float w=11;
        const float h=w*winSize.height/winSize.width;
        m_range.init(-w/2, -w/2+w, -h/2, -h/2+h,
                     -1024,//yeah, better to use negative value
                     1024);
        m_projectionMode=ec3dPerspectiveMode;

    }
    virtual ~Cc3dCamera(){
    
    }
    static Cc3dCamera*create(){
        Cc3dCamera*p=createAutoreleasedObject(p);
        return p;
    }

    Cc3dVector4 getEyePos()const;
    Cc3dVector4 getCenter()const;
    Cc3dVector4 getUp()const;
    void setEyePos(const Cc3dVector4&eyePos);
    void setCenter(const Cc3dVector4&center);
    void setUp(const Cc3dVector4&up);
    float getFovy()const {return m_fovy;}
    float getAspect()const {return m_aspect;}
    float getzNear()const {return m_zNear;}
    float getzFar()const {return m_zFar;}
    void setFovy(float fovy){m_fovy=fovy;}
    void setAspect(float aspect){m_aspect=aspect;}
    void setzNear(float zNear){m_zNear=zNear;}
    void setzFar(float zFar){m_zFar=zFar;}
    Cc3dRange getRange()const {return m_range;}
    void setRange(const Cc3dRange&range){m_range=range;}
    Cc3dMatrix4 calculateViewMat();
    Cc3dMatrix4 calculateViewMatInverse();
    Cc3dMatrix4 calculateProjectionMat();
    Ec3dProjectionMode getProjectionMode(){return m_projectionMode;}
    void setProjectionMode(Ec3dProjectionMode projectionMode){m_projectionMode=projectionMode;}
    void applyProjection();
    void printProjectionMode()const;
protected:
    //projection mode type
    Ec3dProjectionMode m_projectionMode;
    //perspective projection mode params
    float m_fovy;
    float m_aspect;
    float m_zNear;
    float m_zFar;
    //Ortho projection mode params
    Cc3dRange m_range;//in the camera space
protected:
    //cache
    //view matrix may change frequently, so i apply cache for it.
    //but projection matrix not generally not frequently change, so i didn't apply cache for it.
    TCvalueCache<Cc3dMatrix4> m_viewMatCache;
    TCvalueCache<Cc3dMatrix4> m_viewMatInverseCache;
    
    

};
#endif /* defined(__HelloCpp__c3dCamera__) */
