//
//  c3dGLMath.h
//  HelloCpp
//
//  Created by apple on 14-1-5.
//
//

#ifndef __HelloCpp__c3dGLMath__
#define __HelloCpp__c3dGLMath__

#include <iostream>
using namespace std;
#include "c3dMath.h"
//OpenGL transform pipline: http://user.qzone.qq.com/350479720/blog/1310060277
//Basic 3D Math: Matrices: http://www.matrix44.net/cms/notes/opengl-3d-graphics/basic-3d-math-matrices
//ref to kmMat4PerspectiveProjection and kmMat4OrthographicProjection
Cc3dMatrix4 calculateViewMatrixInverse(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);
Cc3dMatrix4 calculateViewMatrix(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);
Cc3dMatrix4 calculateRotationMatrix(const Cc3dVector4&axis,float cosA,float sinA);
Cc3dMatrix4 calculateTranslateMatrix(const Cc3dVector4&translate);
Cc3dMatrix4 calculateScaleMatrix(float kx,float ky,float kz);
Cc3dMatrix4 calculatePerspectiveProjectionMatrix(float fovy,float aspect,float zNear,float zFar);
Cc3dMatrix4 calculateOrthoProjectionMatrix(float left,float right,float bottom,float top,float near,float far);
#endif /* defined(__HelloCpp__c3dGLMath__) */
