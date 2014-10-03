//
//  c3dActor.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#include "c3dModel.h"
void Cc3dModel::addMesh(Cc3dMesh*mesh){
    assert(mesh);
    m_meshList.push_back(mesh);
  //  mesh->setName("?");
    this->addChild(mesh);
    
}
void Cc3dModel::submit(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submit(usage);
    }
}

void Cc3dModel::submitPosition(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submitPosition(usage);
    }
}
void Cc3dModel::submitNormal(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submitNormal(usage);
    }
}
void Cc3dModel::submitColor(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submitColor(usage);
    }
}
void Cc3dModel::submitTexCoord(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submitTexCoord(usage);
    }
}
void Cc3dModel::submitIndex(GLenum usage){
    int nMesh=(int)getMeshCount();
    for(int i=0;i<nMesh;i++){
        Cc3dMesh*mesh=m_meshList[i];
        mesh->submitIndex(usage);
    }
    
}

