//
//  c3dMatrixStackInfoGetor.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-6.
//
//

#include "c3dMatrixStackInfoGetor.h"
// singleton
static Cc3dMatStackInfoGetor *s_sharedMatStackInfoGetor = NULL;
Cc3dMatStackInfoGetor* Cc3dMatStackInfoGetor::sharedMatStackInfoGetor()
{
    if (!s_sharedMatStackInfoGetor)
    {
        s_sharedMatStackInfoGetor = new Cc3dMatStackInfoGetor();
        s_sharedMatStackInfoGetor->init();
    }
    return s_sharedMatStackInfoGetor;
}
Cc3dMatrix4 Cc3dMatStackInfoGetor::getTopMat(Ec3dMatStackName eMatStackName){
    kmMat4 Mat;
    switch (eMatStackName) {
        case ec3dModelViewStack:
            kmGLGetMatrix(KM_GL_MODELVIEW,&Mat);
            break;
        case ec3dProjectionStack:
            kmGLGetMatrix(KM_GL_PROJECTION,&Mat);
            break;
        case ec3dTextureStack:
            kmGLGetMatrix(KM_GL_TEXTURE,&Mat);
            break;
        default:
            assert(false);
            break;
    }
    return Cc3dMatrix4(Mat.mat);
}
Ec3dMatStackName Cc3dMatStackInfoGetor::getCurrentStackName(){
    //ref to kmGLMatrixMode()
    if(current_stack == &modelview_matrix_stack){
        return ec3dModelViewStack;
    }else if(current_stack == &projection_matrix_stack){
        return ec3dProjectionStack;
    }else if(current_stack == &texture_matrix_stack){
        return ec3dTextureStack;
    }else{
        assert(false);
    }
    
}
