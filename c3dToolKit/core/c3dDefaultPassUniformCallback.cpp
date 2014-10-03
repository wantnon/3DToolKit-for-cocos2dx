//
//  c3dDefaultPassUniformCallback.cpp
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-4.
//
//

#include "c3dDefaultPassUniformCallback.h"
#include "c3dSubMesh.h"
#include "c3dLightSource.h"
#include "c3dNode.h"
void passUnifoCallback_texOnly(Cc3dNode*node,Cc3dProgram*program){
    assert(program->getName()=="toolKitRes/shader/c3dTexOnly");
    //do nothing
}
void passUnifoCallback_classicLighting(Cc3dNode*node,Cc3dProgram*program){
    assert(program->getName()=="toolKitRes/shader/c3dClassicLighting");
    Cc3dSubMesh*sprite=(Cc3dSubMesh*)node;
    //----prepare uniform values
    //calculate model mat
    Cc3dMatrix4 modelMat;
    {
        Cc3dMatrix4 VMatInverse,VMMat;
        VMatInverse=sprite->getCamera3D()->calculateViewMatInverse();
        VMMat=Cc3dMatStackInfoGetor::sharedMatStackInfoGetor()->getTopMat(ec3dModelViewStack);
        modelMat=VMatInverse*VMMat;
    }
    //calculate normal mat
    //http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
    //http://www.songho.ca/opengl/gl_normaltransform.html
    //http://www.arcsynthesis.org/gltut/Illumination/Tut09%20Normal%20Transformation.html
    Cc3dMatrix4 normalMat=transpose(inverse(modelMat));
    //other uniform values
    Cc3dVector4 lightPosWorld=sprite->getLightSource()->getWorldPosition3D();
    Cc3dVector4 eyePosWorld=sprite->getCamera3D()->getEyePos();
    Cc3dVector4 diffuseMaterial=sprite->getMaterial()->getDiffuse();
    Cc3dVector4 diffuseLight=sprite->getLightSource()->getDiffuse();
    Cc3dVector4 ambientMaterial=sprite->getMaterial()->getAmbient();
    Cc3dVector4 ambientLight=sprite->getLightSource()->getAmbient();
    Cc3dVector4 specularMaterial=sprite->getMaterial()->getSpecular();
    Cc3dVector4 specularLight=sprite->getLightSource()->getSpecular();
    float shininess=sprite->getMaterial()->getShininess();
    //----pass uniform values
    program->passUnifoValueMatrixNfv("modelMat",modelMat.convertToVector());
    program->passUnifoValueMatrixNfv("normalMat",normalMat.convertToVector());
    program->passUnifoValueNfv("lightPos_world",lightPosWorld.convertToVector());
    program->passUnifoValueNfv("eyePos_world",eyePosWorld.convertToVector());
    program->passUnifoValueNfv("diffuseMaterial", diffuseMaterial.convertToVector());
    program->passUnifoValueNfv("diffuseLight",diffuseLight.convertToVector());
    program->passUnifoValueNfv("ambientMaterial", ambientMaterial.convertToVector());
    program->passUnifoValueNfv("ambientLight", ambientLight.convertToVector());
    program->passUnifoValueNfv("specularMaterial", specularMaterial.convertToVector());
    program->passUnifoValueNfv("specularLight", specularLight.convertToVector());
    program->passUnifoValue1f("shininess", shininess);
};

