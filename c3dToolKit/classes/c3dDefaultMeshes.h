//
//  c3dDefaultMeshes.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#ifndef __HelloCpp__c3dDefaultMeshes__
#define __HelloCpp__c3dDefaultMeshes__

#include <iostream>
using namespace std;
#include "c3dSubMesh.h"
#include "c3dVector.h"
#include "c3dMath.h"
#include "c3dIDTriangle.h"
#include "c3dCommonFunc.h"
Cc3dSubMesh* c3dCreateBoxMesh(float r);
Cc3dSubMesh* c3dCreateBoxMesh(float r,
                           const Cc3dVector4&upFrontLeftVertexColor,const Cc3dVector4&upFrontRightVertexColor,const Cc3dVector4&upBackLeftVertexColor,const Cc3dVector4&upBackRightVertexColor,
                           const Cc3dVector4&dnFrontLeftVertexColor,const Cc3dVector4&dnFrontRightVertexColor,const Cc3dVector4&dnBackLeftVertexColor,const Cc3dVector4&dnBackRightVertexColor);
Cc3dSubMesh* c3dCreateBallMesh(float r,int nSlice,int nStack);
Cc3dSubMesh* c3dCreateBallMesh(float r,int nSlice,int nStack,const Cc3dVector4&northPoleColor,const Cc3dVector4&southPoleColor);
Cc3dSubMesh* c3dCreateConeMesh(float r,float h,int nSlice,int nStack,bool isHaveBottom=true);
Cc3dSubMesh* c3dCreateConeMesh(float r,float h,int nSlice,int nStack,bool isHaveBottom,const Cc3dVector4&headColor,const Cc3dVector4&bottomColor);
#endif /* defined(__HelloCpp__c3dDefaultMeshes__) */
