//
//  c3dSubMeshData.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#ifndef __HelloCpp__c3dSubMeshData__
#define __HelloCpp__c3dSubMeshData__

#include <iostream>
#include "c3dVector.h"
#include "c3dIDTriangle.h"
#include "c3dCommonFunc.h"
class Cc3dSubMeshData:public CCObject
{
public:
    Cc3dSubMeshData(){};
    virtual~Cc3dSubMeshData(){};
    
    bool init(){return true;}
    
    void initPositionList(const float positionArray[],int positionArrayLen);
    void initTexCoordList(const float texCoordArray[],int texCoordArrayLen);
    void initNormalList(const float normalArray[],int normalArrayLen);
    void initColorList(const float colorArray[],int colorArrayLen);
    void initIDtriList(const short indexArray[],int indexArrayLen);
    
    void initPositionList(const vector<Cc3dVector4>&positionList){m_positionList=positionList;};
    void initTexCoordList(const vector<Cc3dVector2>&texCoordList){m_texCoordList=texCoordList;};
    void initNormalList(const vector<Cc3dVector4>&normalList){m_normalList=normalList;};
    void initColorList(const vector<Cc3dVector4>&colorList){m_colorList=colorList;};
    void initIDtriList(const vector<Cc3dIDTriangle>&IDtriList){m_IDtriList=IDtriList;};
    
    int getPositionArrayLen()const{return (int)m_positionList.size()*4;}
    int getTexCoordArrayLen()const{return (int)m_texCoordList.size()*2;}
    int getNormalArrayLen()const{return (int)m_normalList.size()*4;}
    int getColorArrayLen()const{return (int)m_colorList.size()*4;}
    int getIndexArrayLen()const{return (int)m_IDtriList.size()*3;}
    
    const float*getPositionArray(){return m_positionList.front().getArray();}
    const float*getTexCoordArray(){return m_texCoordList.front().getArray();}
    const float*getNormalArray(){return m_normalList.front().getArray();}
    const float*getColorArray(){return m_colorList.front().getArray();}
    const short*getIndexArray(){return m_IDtriList.front().getArray();}
public:
    vector<Cc3dVector4> m_positionList;
    vector<Cc3dVector2> m_texCoordList;
    vector<Cc3dVector4> m_normalList;
    vector<Cc3dVector4> m_colorList;
    vector<Cc3dIDTriangle> m_IDtriList;

};
#endif /* defined(__HelloCpp__c3dSubMeshData__) */
