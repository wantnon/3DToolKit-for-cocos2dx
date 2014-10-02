//
//  c3dNode.h
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-4.
//
//

#ifndef __HelloCpp__c3dNode__
#define __HelloCpp__c3dNode__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dMatrix.h"
#include "c3dMath.h"
#include "c3dVector.h"
#include "c3dCommonFunc.h"
#include "c3dGLMath.h"
#include "c3dCamera.h"
class Cc3dLightSource;
class Cc3dNode:public CCNode
{
public:
    Cc3dNode(){
        m_mat=unitMat();
        m_camera=NULL;
        m_lightSource=NULL;
    }
    virtual~Cc3dNode();
    static Cc3dNode*create();
    virtual bool init();
    virtual void visit();
    virtual bool isSceneNode3D(){return false;}
    //transform
    virtual void setTransform3D(const Cc3dMatrix4&mat);
    virtual Cc3dMatrix4 getTransform3D();
    virtual Cc3dMatrix4 nodeToWorldTransform3D();
    virtual Cc3dMatrix4 worldToNodeTransform3D();
    virtual Cc3dMatrix4 nodeToParentTransform3D();
    virtual Cc3dVector4 convertToWorldSpace3D(const Cc3dVector4&v);
    virtual Cc3dVector4 convertToNodeSpace3D(const Cc3dVector4&v);
    //translate
    virtual void setPosition3D(const Cc3dVector4&position);
    virtual Cc3dVector4 getPosition3D()const;
    virtual Cc3dVector4 getWorldPosition3D();
    virtual void translate3D(const Cc3dVector4&translate);
    virtual void translateRelativeToParent3D(const Cc3dVector4&translate);
    //rotate
    virtual void setRotation3D(const Cc3dVector4&axis,float cosA,float sinA);
    virtual void setRotation3D(const Cc3dVector4&axis,float A);
    virtual Cc3dMatrix4 getRotation3D();
    virtual void rotate3D(const Cc3dVector4&axis,float cosA,float sinA);
    virtual void rotate3D(const Cc3dVector4&axis,float A);
    virtual void rotateRelativeToParent3D(const Cc3dVector4&axis,float cosA,float sinA);
    virtual void rotateRelativeToParent3D(const Cc3dVector4&axis,float A);
    //scale
    virtual void scale3D(float kx,float ky,float kz);
    virtual void scaleRelativeToParent3D(float kx,float ky,float kz);
    Cc3dCamera* getCamera3D(){return m_camera;}
    void setCamera3D(Cc3dCamera*camera);
    //light
    Cc3dLightSource*getLightSource(){return m_lightSource;}
    void setLightSource(Cc3dLightSource*lightSource);
protected:
    virtual void transform3D();
protected:
    Cc3dMatrix4 m_mat;//node to parent transform matrix
    Cc3dCamera*m_camera;
    Cc3dLightSource* m_lightSource;
    
};
#endif /* defined(__HelloCpp__c3dNode__) */
