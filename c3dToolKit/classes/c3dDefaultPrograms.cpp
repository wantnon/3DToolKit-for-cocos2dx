//
//  c3dDefaultPrograms.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#include "c3dDefaultPrograms.h"
Cc3dProgram* c3dGetProgram_c3dTexOnly(){

    string programName="toolKitRes/shader/c3dTexOnly";
    Cc3dProgram*program=(Cc3dProgram*)CCShaderCache::sharedShaderCache()->programForKey(programName.c_str());
    if(program==NULL){
        program=new Cc3dProgram();
        program->autorelease();
        program->init(programName+".vsh", programName+".fsh");
        program->setName(programName);
        //add to shader cache
        CCShaderCache::sharedShaderCache()->addProgram(program, program->getName().c_str());
    }
    return program;
}
Cc3dProgram* c3dGetProgram_c3dClassicLighting(){
    string programName="toolKitRes/shader/c3dClassicLighting";
    Cc3dProgram*program=(Cc3dProgram*)CCShaderCache::sharedShaderCache()->programForKey(programName.c_str());
    if(program==NULL){
        program=new Cc3dProgram();
        program->autorelease();
        program->init(programName+".vsh", programName+".fsh");
        program->setName(programName);
        //attach uniforms
        program->attachUniform("modelMat");
        program->attachUniform("normalMat");
        program->attachUniform("lightPos_world");
        program->attachUniform("eyePos_world");
        program->attachUniform("diffuseMaterial");
        program->attachUniform("diffuseLight");
        program->attachUniform("ambientMaterial");
        program->attachUniform("ambientLight");
        program->attachUniform("specularMaterial");
        program->attachUniform("specularLight");
        program->attachUniform("shininess");
        //add to shader cache
        CCShaderCache::sharedShaderCache()->addProgram(program, program->getName().c_str());
    }
    return program;
}