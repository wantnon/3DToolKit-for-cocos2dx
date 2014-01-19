//
//  c3dSprite.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-2.
//
//

#include "c3dSprite.h"
bool Cc3dSprite::init(){
    this->setAnchorPoint(ccp(0,0));
    //call parent init
    Cc3dNode::init();
    //texture
	CCTexture2D*texture=CCTextureCache::sharedTextureCache()->addImage((c3dDefaultTexPicFolderPath+"defaultTexPic.png").c_str());
    setTexture(texture);
    //material
    Cc3dMaterial*material=Cc3dMaterial::create();
    setMaterial(material);
    //mesh
    Cc3dMesh*mesh=Cc3dMesh::create();//empty mesh
    setMesh(mesh);
    //program
    Cc3dProgram*program=c3dGetProgram_c3dTexOnly();
    setProgram(program);
    //uniformPassor
    Cc3dUniformPassor*uniformPassor=Cc3dUniformPassor::create();
    setUniformPassor(uniformPassor);
    //lightSource
    Cc3dLightSource*lightSource=Cc3dLightSource::create();
    setLightSource(lightSource);
    //indexVBO
    Cc3dIndexVBO3d*indexVBO=Cc3dIndexVBO3d::create();
    setIndexVBO(indexVBO);
    //enable array attribute
    Cc3dIndexVBO3d::enableAttribArrays();
    return true;
}
void Cc3dSprite::setTexture(CCTexture2D*texture){
    assert(texture);
    setRCObject(m_texture, texture);
}
void Cc3dSprite::setMaterial(Cc3dMaterial*material){
    assert(material);
    setRCObject(m_material, material);
}
void Cc3dSprite::setMesh(Cc3dMesh*mesh){
    assert(mesh);
    setRCObject(m_mesh, mesh);
    
};
void Cc3dSprite::setIndexVBO(Cc3dIndexVBO3d*indexVBO){
    assert(indexVBO);
    setRCObject(m_indexVBO, indexVBO);
}
void Cc3dSprite::setProgram(Cc3dProgram*program){
    assert(program);
    setRCObject(m_program, program);
    CCNode::setShaderProgram(m_program);
    
}
void Cc3dSprite::setUniformPassor(Cc3dUniformPassor*uniformPassor){
    assert(uniformPassor);
    setRCObject(m_uniformPassor,uniformPassor);
}
void Cc3dSprite::setLightSource(Cc3dLightSource*lightSource){
    assert(lightSource);
    setRCObject(m_lightSource,lightSource);
}
void Cc3dSprite::submitMesh(GLenum usage){
    submitMeshPosition(usage);
    submitMeshNormal(usage);
    submitMeshColor(usage);
    submitMeshTexCoord(usage);
    submitMeshIndex(usage);
}
void Cc3dSprite::submitMeshPosition(GLenum usage){
    assert(m_mesh);
    assert(m_indexVBO);
    m_indexVBO->submitPosition(m_mesh->getPositionArray(),m_mesh->getPositionArrayLen(),usage);
}
void Cc3dSprite::submitMeshNormal(GLenum usage){
    assert(m_mesh);
    assert(m_indexVBO);
    m_indexVBO->submitNormal(m_mesh->getNormalArray(),m_mesh->getNormalArrayLen(),usage);
}
void Cc3dSprite::submitMeshColor(GLenum usage){
    assert(m_mesh);
    assert(m_indexVBO);
    m_indexVBO->submitColor(m_mesh->getColorArray(),m_mesh->getColorArrayLen(),usage);
}
void Cc3dSprite::submitMeshTexCoord(GLenum usage){
    assert(m_mesh);
    assert(m_indexVBO);
    m_indexVBO->submitTexCoord(m_mesh->getTexCoordArray(),m_mesh->getTexCoordArrayLen(),usage);
}
void Cc3dSprite::submitMeshIndex(GLenum usage){
    assert(m_mesh);
    assert(m_indexVBO);
    m_indexVBO->submitIndex(m_mesh->getIndexArray(),m_mesh->getIndexArrayLen(),usage);
}

void Cc3dSprite::draw(){
    assert(m_mesh&&m_texture&&m_indexVBO
           &&m_program&&m_uniformPassor&&m_lightSource&&m_camera);
    //store isDoDepthTest
    GLboolean isDoDepthTestOld;
    glGetBooleanv(GL_DEPTH_TEST,&isDoDepthTestOld);
    //set depthTest
    if(m_isDoDepthTest!=isDoDepthTestOld){
        CCDirector::sharedDirector()->setDepthTest(m_isDoDepthTest);
    }
    //enable server state (i don't know what this means :( )
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    m_pShaderProgram->use();
    m_pShaderProgram->setUniformsForBuiltins();
    //pass values for my own uniforms
    m_uniformPassor->executeCallback(this, m_program);
    //attach texture to texture attach point
    Cc3dIndexVBO3d::bindTexture(0, m_texture->getName());
    //draw
    m_indexVBO->setPointers();
    m_indexVBO->draw(GL_TRIANGLES);
    Cc3dIndexVBO3d::bindTexture(0, 0);
    //restore isDoDepthTest
    CCDirector::sharedDirector()->setDepthTest(isDoDepthTestOld);
}

bool Cc3dSprite::getIsDoDepthTest()const {
    return m_isDoDepthTest;
}
void Cc3dSprite::setIsDoDepthTest(bool isDoDepthTest){
    m_isDoDepthTest=isDoDepthTest;
    
}
