//
//  c3dActor.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "c3dActor.h"

void Cc3dActor::setModel(Cc3dModel*model){
    if(m_model==NULL){
        m_model=model;
        addChild(m_model);
    }else{
        m_model->removeFromParent();
        m_model=model;
        addChild(m_model);
    }
}
