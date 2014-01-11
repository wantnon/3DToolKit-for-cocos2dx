//
//  c3dScene.h
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#ifndef __HelloCpp__c3dScene__
#define __HelloCpp__c3dScene__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
//#include "support/TransformUtils.h"
#include "c3dCommonFunc.h"
#include "c3dMatrix.h"
#include "c3dMath.h"
#include "c3dNode.h"
#include "c3dCamera.h"

class Cc3dScene:public Cc3dNode
{
public:
    Cc3dScene(){
    }
    virtual~Cc3dScene(){
    
    }
    static Cc3dScene*create(){
        Cc3dScene*p=createAutoreleasedObject(p);
        return p;
    }
    bool init();
    virtual void transform3D();
    virtual void visit();
    virtual bool isSceneNode3D(){return true;}



};
#endif /* defined(__HelloCpp__c3dScene__) */
