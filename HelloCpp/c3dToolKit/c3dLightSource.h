//
//  c3dLightSource.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#ifndef __HelloCpp__c3dLightSource__
#define __HelloCpp__c3dLightSource__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dVector.h"
#include "c3dNode.h"
//light source is a scene node, will be add to scene
class Cc3dLightSource:public Cc3dNode
{
public:
    Cc3dLightSource(){
        //the default values are ref from <<OpenGL Programming Guide>> sixth edition
        m_ambient.init(0, 0, 0, 1);
        m_diffuse.init(1, 1, 1, 1);
        m_specular.init(1, 1, 1, 1);
    }
    ~Cc3dLightSource(){
    }
    static Cc3dLightSource*create(){
        Cc3dLightSource*p=createAutoreleasedObject(p);
        return p;
    }
    Cc3dVector4 getAmbient()const {return m_ambient;}
    Cc3dVector4 getDiffuse()const {return m_diffuse;}
    Cc3dVector4 getSpecular()const {return m_specular;}
    void setAmbient(Cc3dVector4 ambient) {m_ambient=ambient;}
    void setDiffuse(Cc3dVector4 diffuse) {m_diffuse=diffuse;}
    void setSpecular(Cc3dVector4 specular) {m_specular=specular;}
protected:
    Cc3dVector4 m_ambient;
    Cc3dVector4 m_diffuse;
    Cc3dVector4 m_specular;
    
    
};
#endif /* defined(__HelloCpp__c3dLightSource__) */
