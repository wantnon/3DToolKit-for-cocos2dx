//
//  c3dCommonFunc.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#ifndef __HelloCpp__c3dCommonFunc__
#define __HelloCpp__c3dCommonFunc__

#include <iostream>
#include <vector>
using namespace std;
template<class T>
void setRCObject(T &dstObjPtr,const T &srcObjPtr){//set srcObjPtr to dstObjPtr, srcObj and dstObj are all object with reference counting
    if(srcObjPtr==NULL){
        if(dstObjPtr==NULL){
            //do nothing
        }else{//dstObjPtr!=NULL
            dstObjPtr->release();
            dstObjPtr=NULL;
        }
    }else{//srcObjPtr!=NULL
        if(dstObjPtr==NULL){
            dstObjPtr=srcObjPtr;
            dstObjPtr->retain();
        }else{//dstObjPtr!=NULL
            if(dstObjPtr==srcObjPtr){
                //do nothing
            }else{//dstObjPtr!=srcObjPtr
                dstObjPtr->release();
                dstObjPtr=srcObjPtr;
                dstObjPtr->retain();
            }
        }
    }
}

template <class T>
T* createAutoreleasedObject(T*&p){
    p=new T();
    p->autorelease();
    p->init();
    return p;
}

template<class T>
vector<T> connectList(const vector<T>&list1,const vector<T>&list2){
    vector<T> list;
    list=list1;
    int n2=(int)list2.size();
    for(int i=0;i<n2;i++){
        list.push_back(list2[i]);
    }
    return list;
    
}
#endif /* defined(__HelloCpp__c3dCommonFunc__) */
