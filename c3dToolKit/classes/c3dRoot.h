//
//  c3dRoot.h
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-4.
//
//

#ifndef __HelloCpp__c3dRoot__
#define __HelloCpp__c3dRoot__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;

#include "c3dCommonFunc.h"
#include "c3dMatrix.h"
#include "c3dMath.h"
#include "c3dNode.h"
#include "c3dCamera.h"

class Cc3dRoot:public Cc3dNode
{
public:
    Cc3dRoot(){
    }
    virtual~Cc3dRoot(){
    
    }

    bool init();
    virtual void visit();
    virtual bool isSceneNode3D(){return true;}



};
#endif /* defined(__HelloCpp__c3dRoot__) */
