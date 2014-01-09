//
//  c3dUniformPassor.cpp
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#include "c3dUniformPassor.h"
void passUnifoCallback_doNothing(Cc3dNode*node,Cc3dProgram*program){};
Cc3dUniformPassor*Cc3dUniformPassor::createWithCallback(void (*passUniformCallback)(Cc3dNode*, Cc3dProgram*)){
    Cc3dUniformPassor*p=createAutoreleasedObject(p);
    p->setCallback(passUniformCallback);
    return p;
}
void Cc3dUniformPassor::setCallback(void (*callback)(Cc3dNode*, Cc3dProgram*)){
    m_callback=callback;
}
void Cc3dUniformPassor::excuteCallback(Cc3dNode*node, Cc3dProgram*program){
    m_callback(node,program);
}