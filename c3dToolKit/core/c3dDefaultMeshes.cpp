//
//  c3dDefaultMeshes.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#include "c3dDefaultMeshes.h"
Cc3dMesh* c3dCreateConeMesh(float r,float h,int nSlice,int nStack,bool isHaveBottom){
    return c3dCreateConeMesh(r, h, nSlice, nStack, isHaveBottom, cc3dv4(1, 1, 1, 1), cc3dv4(1, 1, 1, 1));
}
Cc3dMesh* c3dCreateConeMesh(float r,float h,int nSlice,int nStack,bool isHaveBottom,const Cc3dVector4&headColor,const Cc3dVector4&bottomColor)
//why cone need nStack ? because even a plane need subdivision to achieve better specular effect
{
    float dA=360.0/nSlice;
    const float PIDIV180=M_PI/180;
    vector<Cc3dVector4> positionList;
    vector<Cc3dVector2> texCoordList;
    vector<Cc3dVector4> normalList;
    vector<Cc3dVector4> colorList;
    vector<Cc3dIDTriangle> IDtriList;
    //----generate side
    //generate positionList, texCoordList, normalList, colorList
    for(int i=0;i<=nStack;i++){
        float y=i*h/nStack;
        for (int j=0; j<=nSlice; j++) {
            float A=j*dA;
            float R=r-i*r/nStack;
            float cosA=cosf(A*PIDIV180);
            float sinA=sinf(A*PIDIV180);
            float x=R*cosA;
            float z=R*sinA;
            Cc3dVector4 position(x,y,z,1);
            float s=(float)j/nSlice+0.25;
            float t=1-(float)i/nStack;
            Cc3dVector2 texCoord(s,t);
            float ny=r/sqrtf(square(h)+square(r));
            float nx,nz;//nx*nx+ny*ny+nz*nz=1 and nx:nz=cosA:sinA => k=sqrt((1-ny*ny)/(cosA*cosA+sinA*sinA)), nx=cosA*k, nz=sinA*k
            float k=sqrtf((1-ny*ny)/(cosA*cosA+sinA*sinA));
            nx=cosA*k;
            nz=sinA*k;
            Cc3dVector4 normal=normalize(cc3dv4(nx,ny,nz,0));
            Cc3dVector4 color=bottomColor*(1-(float)i/nStack)+headColor*((float)i/nStack);
            positionList.push_back(position);
            texCoordList.push_back(texCoord);
            normalList.push_back(normal);
            colorList.push_back(color);
        }
    }
    //generate IDtriList
    for(int i=0;i<nStack;i++){
        for(int j=0;j<nSlice;j++){
            int vID_ld=(nSlice+1)*i+j;
            int vID_rd=vID_ld+1;
            int vID_ru=vID_rd+(nSlice+1);
            int vID_lu=vID_ru-1;
            Cc3dIDTriangle IDtri0(vID_ld,vID_rd,vID_ru);
            Cc3dIDTriangle IDtri1(vID_ld,vID_ru,vID_lu);
            IDtriList.push_back(IDtri0);
            IDtriList.push_back(IDtri1);
        }
    }
   
    //----generate bottom
    if(isHaveBottom){
        vector<Cc3dVector4> _positionList=positionList;
        vector<Cc3dVector2> _texCoordList=texCoordList;
        vector<Cc3dVector4> _normalList=normalList;
        vector<Cc3dVector4> _colorList=colorList;
        vector<Cc3dIDTriangle> _IDtriList=IDtriList;
        //all postion in _positionList set y to zero
        int _nPosition=(int)_positionList.size();
        for(int i=0;i<_nPosition;i++){
            Cc3dVector4&position=_positionList[i];
            position.sety(0);
        }
        //all normal in _normalList set to (0,-1,0,0)
        int _nNormal=(int)_normalList.size();
        for(int i=0;i<_nNormal;i++){
            Cc3dVector4&normal=_normalList[i];
            normal=cc3dv4(0, -1, 0, 0);
        }
        //all index in _IDtriList should be plus offset=(int)positionList.size()
        const int offset=(int)positionList.size();
        int _nIDtri=(int)_IDtriList.size();
        for(int i=0;i<_nIDtri;i++){
            Cc3dIDTriangle&IDtri=_IDtriList[i];
            int ID0=IDtri.vID(0);
            int ID1=IDtri.vID(1);
            int ID2=IDtri.vID(2);
            IDtri.init(ID0+offset, ID1+offset, ID2+offset);
        }
        //connect side and bottom
        positionList=connectList(positionList,_positionList);
        texCoordList=connectList(texCoordList,_texCoordList);
        normalList=connectList(normalList,_normalList);
        colorList=connectList(colorList,_colorList);
        IDtriList=connectList(IDtriList,_IDtriList);
    }

    //----create mesh
    Cc3dSubMeshData*subMeshData=new Cc3dSubMeshData();
    subMeshData->autorelease();
    subMeshData->init();
    subMeshData->initPositionList(positionList);
    subMeshData->initTexCoordList(texCoordList);
    subMeshData->initNormalList(normalList);
    subMeshData->initColorList(colorList);
    subMeshData->initIDtriList(IDtriList);
    Cc3dSubMesh* subMesh=new Cc3dSubMesh();
    subMesh->autorelease();
    subMesh->init();
    subMesh->setSubMeshData(subMeshData);
    Cc3dMesh* mesh=new Cc3dMesh();
    mesh->autorelease();
    mesh->init();
    mesh->addSubMesh(subMesh);
    return mesh;


}
Cc3dMesh* c3dCreateBallMesh(float r,int nSlice,int nStack,const Cc3dVector4&northPoleColor,const Cc3dVector4&southPoleColor)
{
    float dA=360.0/nSlice;
    float dB=180.0/nStack;
    const float PIDIV180=M_PI/180;
    vector<Cc3dVector4> positionList;
    vector<Cc3dVector2> texCoordList;
    vector<Cc3dVector4> normalList;
    vector<Cc3dVector4> colorList;
    vector<Cc3dIDTriangle> IDtriList;
    //generate positionList, texCoordList, normalList, colorList
    for(int i=0;i<=nStack;i++){
        float B=-90+i*dB;
        float y=r*sinf(B*PIDIV180);
        float cosB=cosf(B*PIDIV180);
        for (int j=0; j<=nSlice; j++) {
            float A=j*dA;
            float R=r*cosB;
            float x=R*cosf(A*PIDIV180);
            float z=R*sinf(A*PIDIV180);
            Cc3dVector4 position(x,y,z,1);
            float s=(float)j/nSlice+0.25;
            float t=1-(float)i/nStack;
            Cc3dVector2 texCoord(s,t);
            Cc3dVector4 normal=normalize(cc3dv4(position.x(), position.y(), position.z(), 0));
            Cc3dVector4 color=southPoleColor*(1-(float)i/nStack)+northPoleColor*((float)i/nStack);
            positionList.push_back(position);
            texCoordList.push_back(texCoord);
            normalList.push_back(normal);
            colorList.push_back(color);
        }
    }
    //generate IDtriList
    for(int i=0;i<nStack;i++){
        for(int j=0;j<nSlice;j++){
            int vID_ld=(nSlice+1)*i+j;
            int vID_rd=vID_ld+1;
            int vID_ru=vID_rd+(nSlice+1);
            int vID_lu=vID_ru-1;
            Cc3dIDTriangle IDtri0(vID_ld,vID_rd,vID_ru);
            Cc3dIDTriangle IDtri1(vID_ld,vID_ru,vID_lu);
            IDtriList.push_back(IDtri0);
            IDtriList.push_back(IDtri1);
        }
    }
    Cc3dSubMeshData*subMeshData=new Cc3dSubMeshData();
    subMeshData->autorelease();
    subMeshData->init();
    subMeshData->initPositionList(positionList);
    subMeshData->initTexCoordList(texCoordList);
    subMeshData->initNormalList(normalList);
    subMeshData->initColorList(colorList);
    subMeshData->initIDtriList(IDtriList);
    Cc3dSubMesh* subMesh=new Cc3dSubMesh();
    subMesh->autorelease();
    subMesh->init();
    subMesh->setSubMeshData(subMeshData);
    Cc3dMesh* mesh=new Cc3dMesh();
    mesh->autorelease();
    mesh->init();
    mesh->addSubMesh(subMesh);
    return mesh;
    
}
Cc3dMesh* c3dCreateBallMesh(float r,int nSlice,int nStack){
    return c3dCreateBallMesh(r, nSlice, nStack, cc3dv4(1, 1, 1, 1), cc3dv4(1, 1, 1, 1));
}
Cc3dMesh* c3dCreateBoxMesh(float r,//distance between center and face
                           const Cc3dVector4&upFrontLeftVertexColor,const Cc3dVector4&upFrontRightVertexColor,const Cc3dVector4&upBackLeftVertexColor,const Cc3dVector4&upBackRightVertexColor,
                           const Cc3dVector4&dnFrontLeftVertexColor,const Cc3dVector4&dnFrontRightVertexColor,const Cc3dVector4&dnBackLeftVertexColor,const Cc3dVector4&dnBackRightVertexColor)
//return an autoreleased object
{
    
    // model data
    const int posArrayLen=6*4*4;
	float posArray[posArrayLen]={-r,-r,r,1, r,-r,r,1, r,r,r,1, -r,r,r,1,//front v0~v3
        -r,-r,-r,1, -r,r,-r,1, r,r,-r,1, r,-r,-r,1,//back v4~v7
        -r,r,r,1, r,r,r,1, r,r,-r,1, -r,r,-r,1,//up v8~v11
        -r,-r,r,1, -r,-r,-r,1, r,-r,-r,1, r,-r,r,1,//dn v12~v15
        -r,r,r,1, -r,r,-r,1, -r,-r,-r,1, -r,-r,r,1,//left v16~v19
        r,r,r,1, r,-r,r,1, r,-r,-r,1, r,r,-r,1//right v20~v23
    };
    
    const int normalArrayLen=6*4*4;
    float normalArray[normalArrayLen]={0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0,//front
        0,0,-1,0, 0,0,-1,0, 0,0,-1,0, 0,0,-1,0,//back
        0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0,//up
        0,-1,0,0, 0,-1,0,0, 0,-1,0,0, 0,-1,0,0,//dn
        -1,0,0,0, -1,0,0,0, -1,0,0,0, -1,0,0,0,//left
        1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0//right
    };
    
    const int texCoordArrayLen=6*4*2;
    float texCoordArray[texCoordArrayLen]={0,1, 1,1, 1,0, 0,0,//front
        0,1, 1,1, 1,0, 0,0,//back
        0,1, 1,1, 1,0, 0,0,//up
        0,1, 1,1, 1,0, 0,0,//dn
        0,1, 1,1, 1,0, 0,0,//left
        0,1, 1,1, 1,0, 0,0//right
    };
    
    const int colorArrayLen=6*4*4;
    const float*ufl=upFrontLeftVertexColor.getArray();
    const float*ufr=upFrontRightVertexColor.getArray();
    const float*ubl=upBackLeftVertexColor.getArray();
    const float*ubr=upBackRightVertexColor.getArray();
    const float*dfl=dnFrontLeftVertexColor.getArray();
    const float*dfr=dnFrontRightVertexColor.getArray();
    const float*dbl=dnBackLeftVertexColor.getArray();
    const float*dbr=dnFrontRightVertexColor.getArray();
    float colorArray[colorArrayLen]={
        dfl[0],dfl[1],dfl[2],dfl[3], dfr[0],dfr[1],dfr[2],dfr[3], ufr[0],ufr[1],ufr[2],ufr[3], ufl[0],ufl[1],ufl[2],ufl[3],//front
        dbl[0],dbl[1],dbl[2],dbl[3], ubl[0],ubl[1],ubl[2],ubl[3], ubr[0],ubr[1],ubr[2],ubr[3], dbr[0],dbr[1],dbr[2],dbr[3],//back
        ufl[0],ufl[1],ufl[2],ufl[3], ufr[0],ufr[1],ufr[2],ufr[3], ubr[0],ubr[1],ubr[2],ubr[3], ubl[0],ubl[1],ubl[2],ubl[3],//up
        dfl[0],dfl[1],dfl[2],dfl[3], dbl[0],dbl[1],dbl[2],dbl[3], dbr[0],dbr[1],dbr[2],dbr[3], dfr[0],dfr[1],dfr[2],dfr[3],//dn
        ufl[0],ufl[1],ufl[2],ufl[3], ubl[0],ubl[1],ubl[2],ubl[3], dbl[0],dbl[1],dbl[2],dbl[3], dfl[0],dfl[1],dfl[2],dfl[3],//left
        ufr[0],ufr[1],ufr[2],ufr[3], dfr[0],dfr[1],dfr[2],dfr[3], dbr[0],dbr[1],dbr[2],dbr[3], ubr[0],ubr[1],ubr[2],ubr[3]//right
    };
    
    const int indexArrayLen=6*2*3;
	short indexArray[indexArrayLen]={0,1,2, 2,3,0,//front
        4,5,6, 6,7,4,//back
        8,9,10, 10,11,8,//up
        12,13,14, 14,15,12,//dn
        16,17,18, 18,19,16,//left
        20,21,22, 22,23,20//right
    };
    
    //create mesh
    Cc3dSubMeshData*subMeshData=new Cc3dSubMeshData();
    subMeshData->autorelease();
    subMeshData->init();
    subMeshData->initPositionList(posArray, posArrayLen);
    subMeshData->initNormalList(normalArray, normalArrayLen);
    subMeshData->initColorList(colorArray, colorArrayLen);
    subMeshData->initTexCoordList(texCoordArray, texCoordArrayLen);
    subMeshData->initIDtriList(indexArray, indexArrayLen);
    Cc3dSubMesh* subMesh=new Cc3dSubMesh();
    subMesh->autorelease();
    subMesh->init();
    subMesh->setSubMeshData(subMeshData);
    Cc3dMesh* mesh=new Cc3dMesh();
    mesh->autorelease();
    mesh->init();
    mesh->addSubMesh(subMesh);
    return mesh;
}
Cc3dMesh* c3dCreateBoxMesh(float r){
    return c3dCreateBoxMesh(r,
                            cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1),
                            cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1),cc3dv4(1, 1, 1, 1));
}