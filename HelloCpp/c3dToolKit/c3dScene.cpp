//
//  c3dScene.cpp
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#include "c3dScene.h"
bool Cc3dScene::init(){
    Cc3dNode::init();
    return true;
}
void Cc3dScene::transform3D(){
    //different from ordinary Cc3dNode, for Cc3dScene, we mult matrix and locate camrea as well
    Cc3dNode::transform3D();
    getCamera3D()->locate();
    getCamera3D()->applyProjection();
    
    
}
void Cc3dScene::visit(){
    CCAssert(isUnitMat(nodeToParentTransform3D()), "transformation is not allowed for Cc3dScene!");
    //push matrix
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    //store projection
    ccDirectorProjection projectionModeOld=CCDirector::sharedDirector()->getProjection();
    {
        //set projection
        CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
        //because in CCDirector::setProjection, the modelview matrix is modified, so here we reset it
        kmGLMatrixMode(KM_GL_MODELVIEW);
        kmGLLoadIdentity();
        //call CCLayer's visit
        Cc3dNode::visit();
    }
    //restore projection mode
    //just use setProjection to restore CCDirector::m_eProjection,
    //operations made in setProjection is nonsense for us, and they will be cleaned by following pop matrix
    CCDirector::sharedDirector()->setProjection(projectionModeOld);
    //pop matrix
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
}