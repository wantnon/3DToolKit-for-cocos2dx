//
//  testLayer.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 13-11-6.
//
//

#include "testLayer.h"

bool CtestLayer::init(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    //enable touch
	setTouchEnabled( true );
    //enable update
    scheduleUpdate();
    //update eye pos
    updateEyePos();
    //-----------------------------
    //root3d
    m_root3d=new Cc3dRoot();
    m_root3d->autorelease();
    m_root3d->init();
    m_root3d->setNodeName("root3d");
    this->addChild(m_root3d);
    
    //camera
    Cc3dCamera*camera=m_root3d->getCamera3D();
    camera->setEyePos(cc3dv4(0, 0, m_r, 1));
    camera->setCenter(cc3dv4(0, 0, 0, 1));
    camera->setUp(cc3dv4(0, 1, 0, 0));
    camera->setProjectionMode(ec3dPerspectiveMode);
    //lightSource
    Cc3dLightSource*lightSource=new Cc3dLightSource();
    lightSource->autorelease();
    lightSource->init();
    m_root3d->addChild(lightSource);
    lightSource->setAmbient(cc3dv4(0.8, 0.8, 0.8, 1));
    lightSource->setPosition3D(cc3dv4(60, 90, 120, 1));
    //mesh
    Cc3dSubMesh*subMesh_ball=c3dCreateBallMesh(1, 20, 10, cc3dv4(1, 0.5, 0, 1), cc3dv4(0, 1, 0, 1));
    subMesh_ball->setNodeName("subMesh_ball");
    Cc3dSubMesh*subMesh_box=c3dCreateBoxMesh(1,cc3dv4(1, 0, 0, 1),cc3dv4(0, 1, 0, 1),cc3dv4(0, 0, 1, 1),cc3dv4(1, 1, 0, 1),
                                         cc3dv4(0, 0, 1, 1),cc3dv4(1, 1, 0, 1),cc3dv4(1, 0, 0, 1),cc3dv4(0, 1, 0, 1));
    subMesh_box->setNodeName("subMesh_box");
    Cc3dSubMesh*subMesh_cone=c3dCreateConeMesh(1, 2.7, 20, 10, true, cc3dv4(1, 0, 0, 1), cc3dv4(0, 1, 0, 1));
    subMesh_cone->setNodeName("subMesh_cone");
    //program
    Cc3dProgram*program=c3dGetProgram_c3dClassicLighting();
    //material
    Cc3dMaterial*material=new Cc3dMaterial();
    material->autorelease();
    material->init();
    material->setSpecular(cc3dv4(0.5, 0.5, 0.5, 1));
    material->setShininess(10);
    //texture
    CCTexture2D*tex_logo=CCTextureCache::sharedTextureCache()->addImage("logo.png");
    CCTexture2D*tex_logo2=CCTextureCache::sharedTextureCache()->addImage("logo2.png");

    //sprite
    const int spriteCount=1;
    vector<Cc3dSubMesh*> subMeshList;
    subMeshList.push_back(subMesh_box);
    vector<CCTexture2D*> texList;
    texList.push_back(tex_logo);
    vector<Cc3dVector4> posList;
    posList.push_back(cc3dv4(0, 0, 0, 1));
    for(int i=0;i<spriteCount;i++){
        Cc3dMesh* sprite3d=new Cc3dMesh();
        sprite3d->autorelease();
        sprite3d->init();
        sprite3d->setPosition3D(posList[i]);
        sprite3d->addSubMesh(subMeshList[i]);
        sprite3d->setTexture(texList[i]);
        sprite3d->setLightSource(lightSource);
        sprite3d->setCamera3D(camera);
        sprite3d->setPassUnifoCallback(passUnifoCallback_classicLighting);
        sprite3d->setProgram(program);
        sprite3d->setMaterial(material);
        sprite3d->setNodeName("sprite3d");
        m_root3d->addChild(sprite3d,0);
        m_sprite3dList.push_back(sprite3d);
    }
    //submit sprite3ds
    for(int i=0;i<(int)m_sprite3dList.size();i++){
        Cc3dMesh*sprite3d=m_sprite3dList[i];
        sprite3d->submit(GL_STATIC_DRAW);
    }

    

    //controlButton_swithProjMode
    {
        CCScale9Sprite* btnUp=CCScale9Sprite::create("button.png");
        CCScale9Sprite* btnDn=CCScale9Sprite::create("button_dn.png");
        CCLabelTTF*title=CCLabelTTF::create("proj mode", "Helvetica", 30);
        CCControlButton* controlButton=CCControlButton::create(title, btnUp);
        controlButton->setBackgroundSpriteForState(btnDn,CCControlStateHighlighted);
        controlButton->setPreferredSize(CCSize(180,80));
        controlButton->setPosition(ccp(400,100));
        controlButton->addTargetWithActionForControlEvents(this, (SEL_CCControlHandler)(&CtestLayer::switchProjModeCallBack), CCControlEventTouchDown);
        this->addChild(controlButton);
        m_controlButton_swithProjMode=controlButton;
        
    }
    
    //controlButton_transform
    {
        CCScale9Sprite* btnUp=CCScale9Sprite::create("button.png");
        CCScale9Sprite* btnDn=CCScale9Sprite::create("button_dn.png");
        CCLabelTTF*title=CCLabelTTF::create("transform", "Helvetica", 30);
        CCControlButton* controlButton=CCControlButton::create(title, btnUp);
        controlButton->setBackgroundSpriteForState(btnDn,CCControlStateHighlighted);
        controlButton->setPreferredSize(CCSize(180,80));
        controlButton->setPosition(ccp(700,100));
        controlButton->addTargetWithActionForControlEvents(this, (SEL_CCControlHandler)(&CtestLayer::transformCallBack), CCControlEventTouchDown);
        this->addChild(controlButton);
        m_controlButton_transform=controlButton;
        
    }
    //projection mode label
    m_pLabel=CCLabelTTF::create("proj mode: Perspective", "Arial", 35);
    m_pLabel->setPosition(ccp(origin.x + visibleSize.width*(3.0/4),
                              origin.y + visibleSize.height - m_pLabel->getContentSize().height-100));
    this->addChild(m_pLabel, 1);

    
    return true;
}

void CtestLayer::updateEyePos(){
    float cosA=cosf(m_A*M_PI/180);
    float sinA=sinf(m_A*M_PI/180);
    float cosB=cosf(m_B*M_PI/180);
    float sinB=sinf(m_B*M_PI/180);
    m_eyePos.setx(m_r*cosB*sinA);
    m_eyePos.sety(m_r*sinB);
    m_eyePos.setz(m_r*cosB*cosA);
    m_eyePos.setw(1);
}

void CtestLayer::switchProjModeCallBack(CCObject *senderz, cocos2d::extension::CCControlEvent controlEvent){
    Cc3dCamera*camera=m_root3d->getCamera3D();
    switch(camera->getProjectionMode())
    {
        case ec3dPerspectiveMode:{
            camera->setProjectionMode(ec3dOrthographicMode);
            m_pLabel->setString("proj mode: Orthographic");
        }break;
        case ec3dOrthographicMode:{
            camera->setProjectionMode(ec3dPerspectiveMode);
            m_pLabel->setString("proj mode: Perspective");
        }break;
            
    }
}
void CtestLayer::transformCallBack(CCObject *senderz, CCControlEvent controlEvent){
    if(m_isDoUpdate){
        //restore inital matrix
        int nSprite3d=(int)m_sprite3dList.size();
        for(int i=0;i<nSprite3d;i++){
            m_sprite3dList[i]->setTransform3D(initalMatList[i]);
        }
        //stop update
        m_isDoUpdate=false;
        
    }else{
        //store inital matrix
        initalMatList.clear();
        int nSprite3d=(int)m_sprite3dList.size();
        for(int i=0;i<nSprite3d;i++){
            initalMatList.push_back(m_sprite3dList[i]->getTransform3D());
        }
        //start update
        m_isDoUpdate=true;
    }
}
void CtestLayer::update(float dt){
    if(m_isDoUpdate==false)return;
    m_sprite3dList[0]->rotate3D(cc3dv4(0, 1, 0, 0), 120*dt);

    
}

void CtestLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
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
void CtestLayer::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
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
        m_root3d->getCamera3D()->setEyePos(m_eyePos);
    }
}

void CtestLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint pointInWinSpace = touch->getLocationInView();
        //note: for 3d mode, CCDirector::convertToGL() not works as we expected
        //  CCPoint pointInWinSpace = CCDirector::sharedDirector()->convertToGL(pointInWinSpace);
        
        //----update mos
        m_mosPosf=m_mosPos;
        m_mosPos=pointInWinSpace;
        
    }
}

