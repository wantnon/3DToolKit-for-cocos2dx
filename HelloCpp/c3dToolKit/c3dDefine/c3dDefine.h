//
//  c3dDefine.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#ifndef __HelloCpp__c3dDefine__
#define __HelloCpp__c3dDefine__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;

#define USED_FOR_SUBMIT_TO_VBO final //if used for submit to vbo, it must not contain virtual member function, so it's destructor should not be virtual, so we mark it final

extern int kCCVertexAttrib_Normals;
#define kCCAttributeNameNormal  "a_normal"

#define cc3dv4(x,y,z,w) Cc3dVector4(x,y,z,w)

enum Ec3dMatStackName{
    ec3dModelViewStack = 0,
    ec3dProjectionStack,
    ec3dTextureStack,
};

enum Ec3dProjectionMode{
    ec3dOrthographicMode = 0,
    ec3dPerspectiveMode,
};
#endif /* defined(__HelloCpp__c3dDefine__) */
