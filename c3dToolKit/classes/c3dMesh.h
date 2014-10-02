//
//  c3dMesh.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-11-3.
//
//

#ifndef HelloOpenGL_c3dMesh_h
#define HelloOpenGL_c3dMesh_h
#include "c3dSubMesh.h"



class Cc3dMesh:public Cc3dNode
{

protected:
    vector<Cc3dSubMesh*> m_subMeshList;//网格列表--abc
    
public:
    Cc3dMesh(){

    }
    virtual ~Cc3dMesh(){
        
    }
    int getSubMeshCount()const{return (int)m_subMeshList.size();}
    Cc3dSubMesh*getSubMeshByIndex(int index);
    
    void setIsDoDepthTest(bool isDoDepthTest);
    void setTexture(CCTexture2D*texture);
    void setMaterial(Cc3dMaterial*material);
    void setCamera3D(Cc3dCamera*camera3D);
    void setProgram(Cc3dProgram *program);
    void setPassUnifoCallback(c3dPassUnifoCallbackPtr callback);
    void setLightSource(Cc3dLightSource*light);
    void setIsVisible(bool value);
    void setDiffuse(float r,float g,float b,float a);
    void setAmbient(float r,float g,float b,float a);
    void setSpecular(float r,float g,float b,float a);
    void setShininess(float shininess);
    void submit(GLenum usage);
    void submitVertex(GLenum usage);
    void submitIndex(GLenum usage);
    void addSubMesh(Cc3dSubMesh*submesh);


};




#endif
