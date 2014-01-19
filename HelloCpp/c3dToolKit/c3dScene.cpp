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

void Cc3dScene::visit(){
    //push matrix
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    {
        //apply projection matrix
        getCamera3D()->applyProjection();
        //no matter what the modelview is, set it to identity
        kmGLMatrixMode(KM_GL_MODELVIEW);
        kmGLLoadIdentity();
        //apply view matrix
        getCamera3D()->locate();
        //call Cc3dNode's visit
        Cc3dNode::visit();
    }
    //pop matrix
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
}