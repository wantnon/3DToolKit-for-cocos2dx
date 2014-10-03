//
//  c3dActor.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 12-12-20.
//
//

#ifndef __HelloOpenGL__c3dActor__
#define __HelloOpenGL__c3dActor__

#include <iostream>
#include "c3dModel.h"
class Cc3dActor:public Cc3dNode
{
protected:
    Cc3dModel* m_model;
public:
    Cc3dActor(){
        m_model=NULL;
        init_dft();
    }
    virtual~Cc3dActor(){ 
      
    }
    void init_dft(){
        Cc3dModel*model=new Cc3dModel();
		model->autorelease();
        model->init();
        model->setNodeName("model");
		setModel(model);
    }
    //model access
    void setModel(Cc3dModel*model);
	Cc3dModel*getModel()const {return m_model;}
    //mesh access
    void addMesh(Cc3dMesh*mesh){assert(mesh);m_model->addMesh(mesh);}
	Cc3dMesh* getMeshByIndex(int index){return m_model->getMeshByIndex(index);}
	int getMeshCount(){return m_model->getMeshCount();}
    //----
    void setLightSource(Cc3dLightSource*light){
	//	assert(light);
		this->Cc3dNode::setLightSource(light);
        m_model->setLightSource(light);
    }
    
    void setProgram(Cc3dProgram *program){
    //    assert(program);
		this->Cc3dNode::setProgram(program);
		m_model->setProgram(program);
    }
    void setPassUnifoCallback(c3dPassUnifoCallbackPtr callback){
       // assert(callback);
		this->Cc3dNode::setPassUnifoCallback(callback);
        m_model->setPassUnifoCallback(callback);
        
    }

   	void setIsDoDepthTest(bool value){m_model->setIsDoDepthTest(value);}
    void setCamera3D(Cc3dCamera*camera3D){
        
        this->Cc3dNode::setCamera3D(camera3D);
        
        m_model->setCamera3D(camera3D);
        
    }
    void submitPosition(GLenum usage){m_model->submitPosition(usage);}
    void submitNormal(GLenum usage){m_model->submitNormal(usage);}
    void submitColor(GLenum usage){m_model->submitColor(usage);}
    void submitTexCoord(GLenum usage){m_model->submitTexCoord(usage);}
    void submitIndex(GLenum usage){m_model->submitIndex(usage);}
	void submit(GLenum usage){m_model->submit(usage);}
};



#endif /* defined(__HelloOpenGL__c3dActor__) */
