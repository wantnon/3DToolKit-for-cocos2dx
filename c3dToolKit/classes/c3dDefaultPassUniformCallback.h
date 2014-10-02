//
//  c3dDefaultPassUniformCallback.h
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-4.
//
//

#ifndef __HelloCpp__c3dDefaultPassUniformCallback__
#define __HelloCpp__c3dDefaultPassUniformCallback__

#include <iostream>
using namespace std;
//#include "c3dSprite.h"
#include "c3dNode.h"
#include "c3dProgram.h"
#include "c3dMatrixStackInfoGetor.h"
void passUnifoCallback_texOnly(Cc3dNode*node,Cc3dProgram*program);
void passUnifoCallback_classicLighting(Cc3dNode*node,Cc3dProgram*program);

#endif /* defined(__HelloCpp__c3dDefaultPassUniformCallback__) */
