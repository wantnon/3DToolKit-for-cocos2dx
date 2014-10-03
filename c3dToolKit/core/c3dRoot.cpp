//
//  c3dRoot.cpp
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-4.
//
//

#include "c3dRoot.h"
#include "c3dIndexVBO3d.h"
bool Cc3dRoot::init(){
    this->Cc3dNode::init();
    return true;
}

void Cc3dRoot::visit(){
	
    //store depthTest state
    GLboolean isDoDepthTestOld;
    glGetBooleanv(GL_DEPTH_TEST,&isDoDepthTestOld);
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
    //resotre depthTest state
    CCDirector::sharedDirector()->setDepthTest(isDoDepthTestOld);
	//disable array attribute
////	Cc3dIndexVBO3d::disableAttribArrays();
    
    
    
}