

#include "c3dMesh.h"

Cc3dSubMesh*Cc3dMesh::getSubMeshByIndex(int index){
    assert(index>=0&&index<(int)m_subMeshList.size());
    return m_subMeshList[index];
}

void Cc3dMesh::setIsDoDepthTest(bool isDoDepthTest){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setIsDoDepthTest(isDoDepthTest);
    }
}

void Cc3dMesh::setCamera3D(Cc3dCamera*camera3D){
    
    this->Cc3dNode::setCamera3D(camera3D);
    
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setCamera3D(camera3D);
    }
    
}
void Cc3dMesh::setProgram(Cc3dProgram *program){
    assert(program);
//    this->Cc3dNode::setProgram(program);
    
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setProgram(program);
    }
}
void Cc3dMesh::setPassUnifoCallback(c3dPassUnifoCallbackPtr callback){
    assert(callback);
  //  this->Cc3dNode::setPassUnifoCallback(callback);
    
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setPassUnifoCallback(callback);
    }
    
}
void Cc3dMesh::setLightSource(Cc3dLightSource*light){
    
  //  this->Cc3dNode::setLightSource(light);
    
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setLightSource(light);
    }
}


void Cc3dMesh::setDiffuse(float r,float g,float b,float a){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->getMaterial()->setDiffuse(Cc3dVector4(r, g, b,a));
    }
}
void Cc3dMesh::setTexture(CCTexture2D*texture){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setTexture(texture);
    }
}
void Cc3dMesh::setMaterial(Cc3dMaterial*material){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->setMaterial(material);
    }
}
void Cc3dMesh::setAmbient(float r,float g,float b,float a){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->getMaterial()->setAmbient(Cc3dVector4(r, g, b,a));
    }
    
}
void Cc3dMesh::setSpecular(float r,float g,float b,float a){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->getMaterial()->setSpecular(Cc3dVector4(r, g, b, a));
    }
    
}
void Cc3dMesh::setShininess(float shininess){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh==NULL)continue;
        psubMesh->getMaterial()->setShininess(shininess);
    }
}
void Cc3dMesh::submit(GLenum usage)
{
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submit(usage);
    }
}
void Cc3dMesh::submitPosition(GLenum usage){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submitPosition(usage);
    }
}
void Cc3dMesh::submitNormal(GLenum usage){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submitNormal(usage);
    }
}
void Cc3dMesh::submitColor(GLenum usage){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submitColor(usage);
    }
}
void Cc3dMesh::submitTexCoord(GLenum usage){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submitTexCoord(usage);
    }
}
void Cc3dMesh::submitIndex(GLenum usage){
    int nSubMesh=(int)m_subMeshList.size();
    for(int i=0;i<nSubMesh;i++){
        Cc3dSubMesh*psubMesh=m_subMeshList[i];
        if(psubMesh)psubMesh->submitIndex(usage);
    }
}
void Cc3dMesh::addSubMesh(Cc3dSubMesh*submesh){
    assert(submesh);
    m_subMeshList.push_back(submesh);
    //submesh->setName("?");
    this->addChild(submesh);
    
}
