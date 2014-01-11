//
//  c3dUniformPassor.h
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#ifndef __HelloCpp__c3dUniformPassor__
#define __HelloCpp__c3dUniformPassor__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dProgram.h"
#include "c3dNode.h"
#include "c3dCommonFunc.h"

void passUnifoCallback_doNothing(Cc3dNode*node,Cc3dProgram*program);
class Cc3dUniformPassor:public CCObject
{
public:
    Cc3dUniformPassor(){
        m_callback=passUnifoCallback_doNothing;
    }
    virtual~Cc3dUniformPassor(){
    
    }

    static Cc3dUniformPassor*create(){
        Cc3dUniformPassor*p=createAutoreleasedObject(p);
        return p;
    }
    static Cc3dUniformPassor*createWithCallback(void (*passUniformCallback)(Cc3dNode*, Cc3dProgram*));
    bool init(){return true;}
    void setCallback(void (*callback)(Cc3dNode*, Cc3dProgram*));
    void excuteCallback(Cc3dNode*node, Cc3dProgram*program);
protected:
    void (*m_callback)(Cc3dNode*, Cc3dProgram*);

};
#endif /* defined(__HelloCpp__c3dUniformPassor__) */
