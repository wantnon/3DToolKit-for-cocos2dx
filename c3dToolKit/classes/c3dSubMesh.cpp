//
//  c3dSubMesh.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#include "c3dSubMesh.h"
#include "c3dLightSource.h"
bool Cc3dSubMesh::init(){
    this->setAnchorPoint(ccp(0,0));
    //call parent init
    Cc3dNode::init();
    //texture
	CCTexture2D*texture=CCTextureCache::sharedTextureCache()->addImage("toolKitRes/pic/defaultTexPic.png");
    setTexture(texture);
    //material
    Cc3dMaterial*material=new Cc3dMaterial();
    material->autorelease();
    material->init();
    setMaterial(material);
    //subMeshData
    Cc3dSubMeshData*subMeshData=new Cc3dSubMeshData();//empty subMeshData
    subMeshData->autorelease();
    subMeshData->init();
    setSubMeshData(subMeshData);
    //program
    Cc3dProgram*program=c3dGetProgram_c3dTexOnly();
    setProgram(program);
    //uniformPassor
    m_passUnifoCallback=passUnifoCallback_texOnly;
    //lightSource
    Cc3dLightSource*lightSource=new Cc3dLightSource();
    lightSource->autorelease();
    lightSource->init();
    setLightSource(lightSource);
    //indexVBO
    Cc3dIndexVBO3d*indexVBO=new Cc3dIndexVBO3d();
    indexVBO->autorelease();
    indexVBO->init();
    setIndexVBO(indexVBO);
    return true;
}
void Cc3dSubMesh::setTexture(CCTexture2D*texture){
    assert(texture);
    setRCObject(m_texture, texture);
}
void Cc3dSubMesh::setMaterial(Cc3dMaterial*material){
    assert(material);
    setRCObject(m_material, material);
}
void Cc3dSubMesh::setSubMeshData(Cc3dSubMeshData*subMeshData){
    assert(subMeshData);
    setRCObject(m_subMeshData, subMeshData);
    
};
void Cc3dSubMesh::setIndexVBO(Cc3dIndexVBO3d*indexVBO){
    assert(indexVBO);
    setRCObject(m_indexVBO, indexVBO);
}
void Cc3dSubMesh::submitMesh(GLenum usage){
    submitMeshPosition(usage);
    submitMeshNormal(usage);
    submitMeshColor(usage);
    submitMeshTexCoord(usage);
    submitMeshIndex(usage);
}
void Cc3dSubMesh::submitMeshPosition(GLenum usage){
    assert(m_subMeshData);
    assert(m_indexVBO);
    m_indexVBO->submitPosition(m_subMeshData->getPositionArray(),m_subMeshData->getPositionArrayLen(),usage);
}
void Cc3dSubMesh::submitMeshNormal(GLenum usage){
    assert(m_subMeshData);
    assert(m_indexVBO);
    m_indexVBO->submitNormal(m_subMeshData->getNormalArray(),m_subMeshData->getNormalArrayLen(),usage);
}
void Cc3dSubMesh::submitMeshColor(GLenum usage){
    assert(m_subMeshData);
    assert(m_indexVBO);
    m_indexVBO->submitColor(m_subMeshData->getColorArray(),m_subMeshData->getColorArrayLen(),usage);
}
void Cc3dSubMesh::submitMeshTexCoord(GLenum usage){
    assert(m_subMeshData);
    assert(m_indexVBO);
    m_indexVBO->submitTexCoord(m_subMeshData->getTexCoordArray(),m_subMeshData->getTexCoordArrayLen(),usage);
}
void Cc3dSubMesh::submitMeshIndex(GLenum usage){
    assert(m_subMeshData);
    assert(m_indexVBO);
    m_indexVBO->submitIndex(m_subMeshData->getIndexArray(),m_subMeshData->getIndexArrayLen(),usage);
}

void Cc3dSubMesh::draw(){
    assert(m_subMeshData&&m_texture&&m_indexVBO
           &&m_program&&m_lightSource&&m_camera);
	//enable array attribute
	bool isPostionAttribEnabled=Cc3dIndexVBO3d::isEnabledAttribArray_position();
	bool isTexCoordAttribEnabled=Cc3dIndexVBO3d::isEnabledAttribArray_texCoord();
	bool isNormalAttribEnabled=Cc3dIndexVBO3d::isEnabledAttribArray_normal();
	bool isColorAttribEnabled=Cc3dIndexVBO3d::isEnabledAttribArray_color();
    Cc3dIndexVBO3d::enableAttribArray_position(true);
	Cc3dIndexVBO3d::enableAttribArray_texCoord(true);
	Cc3dIndexVBO3d::enableAttribArray_normal(true);
	Cc3dIndexVBO3d::enableAttribArray_color(true);
    //apply state
    //for performance sake, we only apply state, not restore
    {
        //set depthTest
        CCDirector::sharedDirector()->setDepthTest(m_isDoDepthTest);
        //set blend function
        ccGLBlendFunc(m_blendFunc.src, m_blendFunc.dst);
    }
    
    //enable server state (i don't know what this means :( )
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    m_pShaderProgram->use();
    m_pShaderProgram->setUniformsForBuiltins();
    //pass values for my own uniforms
    m_passUnifoCallback(this, m_program);
    //attach texture to texture attach point
    Cc3dIndexVBO3d::bindTexture(0, m_texture->getName());
    //draw
    m_indexVBO->setPointers();
    m_indexVBO->draw(GL_TRIANGLES);
    Cc3dIndexVBO3d::bindTexture(0, 0);
	//recover array attribute state
	Cc3dIndexVBO3d::enableAttribArray_position(isPostionAttribEnabled);
	Cc3dIndexVBO3d::enableAttribArray_texCoord(isTexCoordAttribEnabled);
	Cc3dIndexVBO3d::enableAttribArray_normal(isNormalAttribEnabled);
	Cc3dIndexVBO3d::enableAttribArray_color(isColorAttribEnabled);
}

bool Cc3dSubMesh::getIsDoDepthTest()const {
    return m_isDoDepthTest;
}
void Cc3dSubMesh::setIsDoDepthTest(bool isDoDepthTest){
    m_isDoDepthTest=isDoDepthTest;
    
}
