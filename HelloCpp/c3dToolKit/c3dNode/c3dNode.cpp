//
//  c3dNode.cpp
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#include "c3dNode.h"
Cc3dNode*Cc3dNode::create(){
    Cc3dNode*p=createAutoreleasedObject(p);
    return p;
}
bool Cc3dNode::init(){
    //camera
    Cc3dCamera*camera=Cc3dCamera::create();
    setCamera3D(camera);
    return true;
};
void Cc3dNode::setCamera3D(Cc3dCamera*camera){
    assert(camera);
    setRCObject(m_camera, camera);
}
Cc3dVector4 Cc3dNode::getPosition3D()const {
    Cc3dVector4 position(m_mat.getAt(12),m_mat.getAt(13),m_mat.getAt(14),1);
    return position;
}
Cc3dVector4 Cc3dNode::getWorldPosition3D() {
    return convertToWorldSpace3D(cc3dv4(0, 0, 0, 1));
}
void Cc3dNode::setPosition3D(const Cc3dVector4&position){
    m_mat.setAt(12, position.x());
    m_mat.setAt(13, position.y());
    m_mat.setAt(14, position.z());
}
Cc3dMatrix4 Cc3dNode::nodeToWorldTransform3D()
{
    Cc3dMatrix4 t = this->m_mat;
    for (Cc3dNode *p = (Cc3dNode*)this->getParent(); p != NULL; p = (Cc3dNode*)p->getParent()){
        if(p->isSceneNode3D())break;//seneNode's matrix do not count in
        t = p->nodeToParentTransform3D()*t;
    }
    return t;
}
Cc3dMatrix4 Cc3dNode::worldToNodeTransform3D(){
    Cc3dMatrix4 nodeToWorld=nodeToWorldTransform3D();
    Cc3dMatrix4 worldToNode=inverse(nodeToWorld);
    return worldToNode;
}
Cc3dVector4 Cc3dNode::convertToWorldSpace3D(const Cc3dVector4&v)
{
    Cc3dMatrix4 nodeToWorldTransform=nodeToWorldTransform3D();
    Cc3dVector4 rs=nodeToWorldTransform*v;
    return rs;
}
Cc3dVector4 Cc3dNode::convertToNodeSpace3D(const Cc3dVector4&v){
    Cc3dMatrix4 worldToNodeTransform=worldToNodeTransform3D();
    Cc3dVector4 rs=worldToNodeTransform*v;
    return rs;
}

Cc3dMatrix4 Cc3dNode::nodeToParentTransform3D(){
    return m_mat;
}

void Cc3dNode::transform3D(){//used in visit()
    //for ordinary Cc3dNode, we only mult matrix, not locate camrea
    kmMat4 transfrom4x4;
    memcpy(transfrom4x4.mat, m_mat.getArray(), 16*sizeof(float));
    kmGLMultMatrix( &transfrom4x4 );
}

void Cc3dNode::rotate3D(const Cc3dVector4&axis,float cosA,float sinA){
    //axis must be a unit vector
    assert(axis.w()==0);
    assert(getLength2(axis)==1);
    Cc3dMatrix4 RMat=calculateRotationMatrix(axis, cosA, sinA);
    m_mat=m_mat*RMat;
};
void Cc3dNode::rotateRelativeToParent3D(const Cc3dVector4&axis,float cosA,float sinA){
    //axis must be a unit vector
    assert(axis.w()==0);
    assert(getLength2(axis)==1);
    Cc3dMatrix4 RMat=calculateRotationMatrix(axis, cosA, sinA);
    m_mat=RMat*m_mat;
    
}
void Cc3dNode::translate3D(const Cc3dVector4&translate){
    assert(translate.w()==0);
    Cc3dMatrix4 TMat=calculateTranslateMatrix(translate);
    m_mat=m_mat*TMat;
}
void Cc3dNode::translateRelativeToParent3D(const Cc3dVector4&translate){
    assert(translate.w()==0);
    Cc3dMatrix4 TMat=calculateTranslateMatrix(translate);
    m_mat=TMat*m_mat;
    
}
void Cc3dNode::setRotation3D(const Cc3dVector4&axis,float cosA,float sinA){
    assert(axis.w()==0);
    Cc3dMatrix4 RMat=calculateRotationMatrix(axis, cosA, sinA);
    //replace left up 3x3 sub matrix of m_mat with RMat
    const int indexs[9]={0,1,2,4,5,6,8,9,10};
    for(int i=0;i<9;i++){
        int index=indexs[i];
        m_mat.setAt(index, RMat.getAt(index));
    }
}
void Cc3dNode::rotate3D(const Cc3dVector4&axis,float A){
    rotate3D(axis, cosf(A*M_PI/180), sinf(A*M_PI/180));
}
void Cc3dNode::setRotation3D(const Cc3dVector4&axis,float A){
    setRotation3D(axis, cosf(A*M_PI/180), sinf(A*M_PI/180));
}
void Cc3dNode::rotateRelativeToParent3D(const Cc3dVector4&axis,float A){
    rotateRelativeToParent3D(axis, cosf(A*M_PI/180), sinf(A*M_PI/180));
}

Cc3dMatrix4 Cc3dNode::getRotation3D(){
    Cc3dMatrix4 RMat=unitMat();
    //replace left up 3x3 sub matrix of RMat with m_mat
    const int indexs[9]={0,1,2,4,5,6,8,9,10};
    for(int i=0;i<9;i++){
        int index=indexs[i];
        RMat.setAt(index, m_mat.getAt(index));
    }
    return RMat;
}
void Cc3dNode::setTransform3D(const Cc3dMatrix4&mat){
    m_mat=mat;
}
Cc3dMatrix4 Cc3dNode::getTransform3D(){
    return m_mat;
}
void Cc3dNode::scale3D(float kx,float ky,float kz){
    Cc3dMatrix4 SMat=calculateScaleMatrix(kx, ky, kz);
    m_mat=m_mat*SMat;
}
void Cc3dNode::scaleRelativeToParent3D(float kx,float ky,float kz){
    Cc3dMatrix4 SMat=calculateScaleMatrix(kx, ky, kz);
    m_mat=SMat*m_mat;
}

//for 3d drawing, fake zOrder is also useful,
//because some times we need to control the drawing order, then we can use it.
void Cc3dNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    kmGLPushMatrix();
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
    }
    
    this->transform3D();
    
    Cc3dNode* pNode = NULL;
    unsigned int i = 0;
    
    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (Cc3dNode*) arrayData->arr[i];
            
            if ( pNode && pNode->getZOrder() < 0 )
            {
                pNode->visit();
            }
            else
            {
                break;
            }
        }
        // self draw
        this->draw();
        
        for( ; i < arrayData->num; i++ )
        {
            pNode = (Cc3dNode*) arrayData->arr[i];
            if (pNode)
            {
                pNode->visit();
            }
        }
    }
    else
    {
        this->draw();
    }
    
    // reset for next frame
    m_uOrderOfArrival = 0;
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }
    
    kmGLPopMatrix();
}
