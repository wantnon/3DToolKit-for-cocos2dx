//
//  scene3DLayer.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 13-11-6.
//
//

#include "scene3DLayer.h"

bool Cscene3DLayer::init(){
    //enable touch
	setTouchEnabled( true );
    //update eye pos
    updateEyePos();
    
    //scene
    m_scene=Cc3dScene::create();
    this->addChild(m_scene);
    
    //camera
    Cc3dCamera*camera=m_scene->getCamera3D();
    camera->setEyePos(cc3dv4(0, 0, m_r, 1));
    camera->setCenter(cc3dv4(0, 0, 0, 1));
    camera->setUp(cc3dv4(0, 1, 0, 0));
    camera->setProjectionMode(ec3dPerspectiveMode);
    //lightSource
    Cc3dLightSource*lightSource=Cc3dLightSource::create();
    m_scene->addChild(lightSource);
    lightSource->setAmbient(cc3dv4(0.8, 0.8, 0.8, 1));
    lightSource->setPosition3D(cc3dv4(60, 90, 120, 1));
    //mesh
    Cc3dMesh*mesh_ball=c3dCreateBallMesh(1, 20, 10, cc3dv4(1, 0.5, 0, 1), cc3dv4(0, 1, 0, 1));
    Cc3dMesh*mesh_box=c3dCreateBoxMesh(1,cc3dv4(1, 0, 0, 1),cc3dv4(0, 1, 0, 1),cc3dv4(0, 0, 1, 1),cc3dv4(1, 1, 0, 1),
                                         cc3dv4(0, 0, 1, 1),cc3dv4(1, 1, 0, 1),cc3dv4(1, 0, 0, 1),cc3dv4(0, 1, 0, 1));
    Cc3dMesh*mesh_cone=c3dCreateConeMesh(1, 2.7, 20, 10, true, cc3dv4(1, 0, 0, 1), cc3dv4(0, 1, 0, 1));
    //program
    Cc3dProgram*program=c3dGetProgram_c3dClassicLighting();
    //material
    Cc3dMaterial*material=Cc3dMaterial::create();
    material->setSpecular(cc3dv4(0.5, 0.5, 0.5, 1));
    material->setShininess(10);
    //texture
    CCTexture2D*tex_logo=CCTextureCache::sharedTextureCache()->addImage("logo.png");
    CCTexture2D*tex_logo2=CCTextureCache::sharedTextureCache()->addImage("logo2.png");
    //unifoPassor
    Cc3dUniformPassor*uniformPassor=Cc3dUniformPassor::createWithCallback(passUnifoCallback_classicLighting);
    
    //sprite
    const int spriteCount=3;
    vector<Cc3dMesh*> meshList;
    meshList.push_back(mesh_box);
    meshList.push_back(mesh_cone);
    meshList.push_back(mesh_ball);
    vector<CCTexture2D*> texList;
    texList.push_back(tex_logo);
    texList.push_back(tex_logo);
    texList.push_back(tex_logo2);
    for(int i=0;i<spriteCount;i++){
        Cc3dSprite* sprite=Cc3dSprite::create();
        m_spriteList.push_back(sprite);
        m_scene->addChild(sprite,0);
        sprite->setMesh(meshList[i]);
        sprite->setLightSource(lightSource);
        sprite->setCamera3D(camera);
        sprite->setUniformPassor(uniformPassor);
        sprite->setProgram(program);
        sprite->setMaterial(material);
        sprite->setTexture(texList[i]);
        sprite->submitMesh(GL_STATIC_DRAW);
    }
    m_spriteList[0]->setPosition3D(cc3dv4(-2.5, 0, 0, 1));
    m_spriteList[1]->setPosition3D(cc3dv4(0, -1, 0, 1));
    m_spriteList[2]->setPosition3D(cc3dv4(2.5, 0, 0, 1));

    
    return true;
}

void Cscene3DLayer::updateEyePos(){
    float cosA=cosf(m_A*M_PI/180);
    float sinA=sinf(m_A*M_PI/180);
    float cosB=cosf(m_B*M_PI/180);
    float sinB=sinf(m_B*M_PI/180);
    m_eyePos.setx(m_r*cosB*sinA);
    m_eyePos.sety(m_r*sinB);
    m_eyePos.setz(m_r*cosB*cosA);
    m_eyePos.setw(1);
}

void Cscene3DLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint pointInWinSpace = touch->getLocationInView();
        
        //----update mos
        m_mosPosf=m_mosPos;
        m_mosPos=pointInWinSpace;
        
    }
}
void Cscene3DLayer::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint pointInWinSpace = touch->getLocationInView();
       
        //----update mos
        m_mosPosf=m_mosPos;
        m_mosPos=pointInWinSpace;
        //----update eyePos
        m_A+=-(m_mosPos.x-m_mosPosf.x)*0.4;
        m_B+=(m_mosPos.y-m_mosPosf.y)*0.4;
        if(m_B>89.9)m_B=89.9;
        if(m_B<-89.9)m_B=-89.9;
        updateEyePos();
        m_scene->getCamera3D()->setEyePos(m_eyePos);
    }
}

void Cscene3DLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint pointInWinSpace = touch->getLocationInView();
        //for 3d mode, CCDirector::convertToGL() not works as we expected
        //  CCPoint pointInWinSpace = CCDirector::sharedDirector()->convertToGL(pointInWinSpace);
        //  CCLOG("pointInWinSpace:%f,%f",pointInWinSpace.x,pointInWinSpace.y);
        
        //----update mos
        m_mosPosf=m_mosPos;
        m_mosPos=pointInWinSpace;
        
    }
}

