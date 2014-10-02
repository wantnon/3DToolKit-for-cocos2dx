//
//  c3dSubMesh.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#ifndef __HelloCpp__c3dSubMesh__
#define __HelloCpp__c3dSubMesh__

#include "cocos2d.h"
using namespace cocos2d;
#include<iostream>
using namespace std;
#include "c3dNode.h"

#include "c3dMatrix.h"
#include "c3dVector.h"
#include "c3dIndexVBO3d.h"
#include "c3dSubMeshData.h"
#include "c3dDefine.h"
#include "c3dCommonFunc.h"
#include "c3dDefaultPrograms.h"

#include "c3dMaterial.h"
#include "c3dCamera.h"
#include "c3dDefine.h"

class Cc3dSubMesh : public Cc3dNode{
public:
	Cc3dSubMesh() {
        m_texture=NULL;
        m_subMeshData=NULL;
        m_indexVBO=NULL;
        m_lightSource=NULL;
        m_material=NULL;
        m_isDoDepthTest=true;
        m_blendFunc.src=C3D_BLEND_SRC;
        m_blendFunc.dst=C3D_BLEND_DST;
    }
	virtual ~Cc3dSubMesh(){
        if(m_texture)m_texture->release();
        if(m_subMeshData)m_subMeshData->release();
        if(m_indexVBO)m_indexVBO->release();
        if(m_material)m_material->release();
    };

    bool init();
    void setTexture(CCTexture2D*texture);
    void setMaterial(Cc3dMaterial*material);
    void setSubMeshData(Cc3dSubMeshData*subMeshData);
    void setIndexVBO(Cc3dIndexVBO3d*indexVBO);
    
    void submitMesh(GLenum usage);
    void submitMeshPosition(GLenum usage);
    void submitMeshNormal(GLenum usage);
    void submitMeshColor(GLenum usage);
    void submitMeshTexCoord(GLenum usage);
    void submitMeshIndex(GLenum usage);
	void draw();

    Cc3dMaterial*getMaterial(){return m_material;}
    bool getIsDoDepthTest()const;
    void setIsDoDepthTest(bool isDoDepthTest);
    void setBlendFunc(ccBlendFunc blendFunc){m_blendFunc = blendFunc;}
    ccBlendFunc getBlendFunc(){return m_blendFunc;}
protected:
    CCTexture2D* m_texture;
    Cc3dMaterial* m_material;
    Cc3dSubMeshData* m_subMeshData;
    Cc3dIndexVBO3d* m_indexVBO;


    bool m_isDoDepthTest;
    ccBlendFunc m_blendFunc;
    
    
};

#endif /* defined(__HelloCpp__c3dSubMesh__) */
