//
//  c3dValueCache.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-7.
//
//

#ifndef __HelloCpp__c3dValueCache__
#define __HelloCpp__c3dValueCache__

#include <iostream>
using namespace std;
#include "c3dDefine.h"

template <typename T>
class TCvalueCache C3DFINAL
{
public:
    TCvalueCache(){
        m_isDirty=true;
    }
    ~TCvalueCache(){}
    bool getIsDirty()const {return m_isDirty;}
    void setIsDirty(bool isDirty){m_isDirty=isDirty;}
    void cacheValue(const T&value){m_value=value;};
    T getValue()const{return m_value;}
protected:
    T m_value;
    bool m_isDirty;
};

#endif /* defined(__HelloCpp__c3dValueCache__) */
