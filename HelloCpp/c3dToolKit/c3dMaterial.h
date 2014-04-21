//
//  c3dMaterial.h
//  HelloCpp
//
//  Created by apple on 14-1-5.
//
//

#ifndef __HelloCpp__c3dMaterial__
#define __HelloCpp__c3dMaterial__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dCommonFunc.h"
#include "c3dVector.h"
class Cc3dMaterial:public CCObject
{
public:
    Cc3dMaterial(){
        //the default values are ref from <<OpenGL Programming Guide>> sixth edition
        m_ambient.init(0.2, 0.2, 0.2, 1);
        m_diffuse.init(0.8, 0.8, 0.8, 1);
        m_specular.init(0, 0, 0, 1);
    }
    virtual~Cc3dMaterial(){
        
    }
    static Cc3dMaterial*create(){
        Cc3dMaterial*p=createAutoreleasedObject(p);
        return p;
    }
    bool init(){return true;}
    Cc3dVector4 getAmbient()const {return m_ambient;}
    Cc3dVector4 getDiffuse()const {return m_diffuse;}
    Cc3dVector4 getSpecular()const {return m_specular;}
    float getShininess()const {return m_shininess;}
    void setAmbient(Cc3dVector4 ambient) {m_ambient=ambient;}
    void setDiffuse(Cc3dVector4 diffuse) {m_diffuse=diffuse;}
    void setSpecular(Cc3dVector4 specular) {m_specular=specular;}
    void setShininess(float shininess){m_shininess=shininess;}
protected:
    Cc3dVector4 m_ambient;
    Cc3dVector4 m_diffuse;
    Cc3dVector4 m_specular;
    float m_shininess;
};
#endif /* defined(__HelloCpp__c3dMaterial__) */
