//
//  c3dSprite.h
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#ifndef __HelloCpp__c3dSprite__
#define __HelloCpp__c3dSprite__

#include "cocos2d.h"
using namespace cocos2d;
#include<iostream>
using namespace std;
#include "c3dNode.h"
#include "c3dProgram.h"
#include "c3dMatrix.h"
#include "c3dVector.h"
#include "c3dIndexVBO3d.h"
#include "c3dMesh.h"
#include "c3dDefine.h"
#include "c3dCommonFunc.h"
#include "c3dDefaultPrograms.h"

#include "c3dMaterial.h"
#include "c3dCamera.h"
#include "c3dDefine.h"
#include "c3dDefaultPassUniformCallback.h"
typedef void(*c3dPassUnifoCallbackPtr)(Cc3dNode*, Cc3dProgram*);
class Cc3dSprite : public Cc3dNode{
public:
	Cc3dSprite() {
        m_texture=NULL;
        m_mesh=NULL;
        m_indexVBO=NULL;
        m_program=NULL;
        m_passUnifoCallback=NULL;
        m_lightSource=NULL;
        m_material=NULL;
        m_isDoDepthTest=true;
        m_blendFunc.src=C3D_BLEND_SRC;
        m_blendFunc.dst=C3D_BLEND_DST;
    }
	virtual ~Cc3dSprite(){
        if(m_texture)m_texture->release();
        if(m_mesh)m_mesh->release();
        if(m_indexVBO)m_indexVBO->release();
        if(m_program)m_program->release();
        if(m_material)m_material->release();
    };

    bool init();
    void setTexture(CCTexture2D*texture);
    void setMaterial(Cc3dMaterial*material);
    void setMesh(Cc3dMesh*mesh);
    void setIndexVBO(Cc3dIndexVBO3d*indexVBO);
    void setProgram(Cc3dProgram*program);
    void setPassUnifoCallback(c3dPassUnifoCallbackPtr passUnifoCallback);
    void setLightSource(Cc3dLightSource*lightSource);
    void submitMesh(GLenum usage);
    void submitMeshPosition(GLenum usage);
    void submitMeshNormal(GLenum usage);
    void submitMeshColor(GLenum usage);
    void submitMeshTexCoord(GLenum usage);
    void submitMeshIndex(GLenum usage);
	void draw();

    Cc3dMaterial*getMaterial()const{return m_material;}
    bool getIsDoDepthTest()const;
    void setIsDoDepthTest(bool isDoDepthTest);
    void setBlendFunc(ccBlendFunc blendFunc){m_blendFunc = blendFunc;}
    ccBlendFunc getBlendFunc(){return m_blendFunc;}
protected:
    CCTexture2D* m_texture;
    Cc3dMaterial* m_material;
    Cc3dMesh* m_mesh;
    Cc3dIndexVBO3d* m_indexVBO;
    Cc3dProgram* m_program;
    c3dPassUnifoCallbackPtr m_passUnifoCallback;

    bool m_isDoDepthTest;
    ccBlendFunc m_blendFunc;
    
    
};

#endif /* defined(__HelloCpp__c3dSprite__) */
