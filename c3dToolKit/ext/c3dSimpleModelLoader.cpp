//
//  c3dSimpleModelLoader.cpp
//  HelloCpp
//
//  Created by apple on 14-10-3.
//
//

#include "c3dSimpleModelLoader.h"
Cc3dActor* c3dSimpleLoadActor(string path){
    //----Cc3dSkinActor.txt
    Cc3dActor*actor=new Cc3dActor();
    actor->autorelease();
    actor->init();
    Cc3dModel*model=new Cc3dModel();
    model->autorelease();
    model->init();
    int skinMeshCount;
    bool valueOnly;
    {
        string fullpath=CCFileUtils::sharedFileUtils()->fullPathForFilename((path+"/Cc3dSkinActor.txt").c_str());
        //open file
		FILE  *fp=NULL;
		fp=fopen(fullpath.c_str(),"r");//override write
		if(fp==NULL){
			cout<<"Open "<<fullpath<<" failed!"<<endl;
			assert(false);
		}
		//------------------read file
		char t_str[1024];
		fscanf(fp,"%s",t_str);
		string str=t_str;
		if(str=="valueOnly"){
			valueOnly=true;
		}else if(str=="notValueOnly"){
			valueOnly=false;
		}else{
			assert(false);
		}
		cout<<"valueOnly:"<<valueOnly<<endl;
        
		fskipOneStr(fp,valueOnly);
        int aniLayerIndex;
		fscanf(fp,"%i",&aniLayerIndex);
        
		fskipOneStr(fp,valueOnly);
        float interval;
		fscanf(fp,"%f",&interval);
        
		fskipOneStr(fp,valueOnly);
		int t_nAniLayerInfo;
		fscanf(fp,"%i",&t_nAniLayerInfo);
        
		fskipOneStr(fp,valueOnly);
		int t_nSkinMesh;
		fscanf(fp,"%i",&t_nSkinMesh);
        
		//--------------------------close file
		fclose(fp);
        //----
        skinMeshCount=t_nSkinMesh;

    }
    
    //----m_skinMesh_0 ~ m_skinMesh_[skinMeshCount-1]
    for(int skinMeshIndex=0;skinMeshIndex<skinMeshCount;skinMeshIndex++){
        //----Cc3dSkinMesh.txt
        Cc3dMesh* mesh=new Cc3dMesh();
        mesh->autorelease();
        mesh->init();
        int skinSubMeshCount;
        {
            string fullpath=CCFileUtils::sharedFileUtils()->fullPathForFilename((path+"/m_skinMesh_"+numberToStr(skinMeshIndex)+"/Cc3dSkinMesh.txt").c_str());
            //open file
            FILE  *fp=NULL;
            fp=fopen(fullpath.c_str(),"r");//override write
            if(fp==NULL){
                cout<<"Open "<<fullpath<<" failed!"<<endl;
                assert(false);
            }
            //------------------read file
            
            fskipOneStr(fp,valueOnly);
            int t_nSkinSubMesh;
            fscanf(fp,"%i",&t_nSkinSubMesh);
            if(!valueOnly)assert(string(tCharBuffer)=="m_skinSubMesh.size");
            
            fskipOneStr(fp,valueOnly);
            int t_nVertexDup;
            fscanf(fp,"%i",&t_nVertexDup);
            if(!valueOnly)assert(string(tCharBuffer)=="m_vertexDupList.size");
            assert(t_nVertexDup==0);
            //RTmat and Scale
            float m[16];
            fskipOneStr(fp,valueOnly);
            if(!valueOnly)assert(string(tCharBuffer)=="RTmat");
            for(int j=0;j<16;j++){
                fscanf(fp,"%f",&m[j]);
            }
            Cc3dMatrix4 t_RTmat(m);
            float t_scaleX,t_scaleY,t_scaleZ;
            fskipOneStr(fp,valueOnly);
            if(!valueOnly)assert(string(tCharBuffer)=="scale");
            fscanf(fp,"%f",&t_scaleX);
            fscanf(fp,"%f",&t_scaleY);
            fscanf(fp,"%f",&t_scaleZ);
            //--------------------------close file
            fclose(fp);
            //---
            skinSubMeshCount=t_nSkinSubMesh;
            
            mesh->setTransform3D(t_RTmat);
            mesh->scale3D(t_scaleX, t_scaleY, t_scaleZ);
        }
        //----m_skinSubMesh_0 ~ m_skinSubMesh_[skinSubMeshCount-1]
        for(int skinSubMeshIndex=0;skinSubMeshIndex<skinSubMeshCount;skinSubMeshIndex++){
         
            //----Cc3dSkinSubMesh.txt
            Cc3dSubMesh*subMesh=new Cc3dSubMesh();
            subMesh->autorelease();
            subMesh->init();
            {
                string fullpath=CCFileUtils::sharedFileUtils()->fullPathForFilename((path+"/m_skinMesh_"+numberToStr(skinMeshIndex)+
                                                                                     "/m_skinSubMesh_"+numberToStr(skinSubMeshIndex)+
                                                                                     "/Cc3dSkinSubMesh.txt").c_str());
                //open file
                FILE  *fp=NULL;
                fp=fopen(fullpath.c_str(),"r");//override write
                if(fp==NULL){
                    cout<<"Open "<<fullpath<<" failed!"<<endl;
                    assert(false);
                }
                
                //------------------read file
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="texFilePath");
                char t_texFilePathRelativeToModelPath[1024];
                fscanf(fp,"%s",t_texFilePathRelativeToModelPath);
                string texFilePathRelativeToModelPath=string(t_texFilePathRelativeToModelPath);
                string texFilePath=path+"/"+texFilePathRelativeToModelPath;
                CCTexture2D*t_texture=CCTextureCache::sharedTextureCache()->addImage(texFilePath.c_str());
                
                Cc3dVector4 ambient;
                Cc3dVector4 diffuse;
                Cc3dVector4 specular;
                float shininess;
                
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="ambient");
                ambient=fscanVector4(fp);
                
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="diffuse");
                diffuse=fscanVector4(fp);
                
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="specular");
                specular=fscanVector4(fp);
                
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="shininess");
                fscanf(fp,"%f",&shininess);
                
                Cc3dMaterial*t_material=new Cc3dMaterial();
                t_material->autorelease();
                t_material->setAmbient(ambient);
                t_material->setDiffuse(diffuse);
                t_material->setSpecular(specular);
                t_material->setShininess(shininess);
                
                //--------------------------close file
                fclose(fp);
                //----
                subMesh->setTexture(t_texture);
                subMesh->setMaterial(t_material);
            
            }
            //----m_subMeshData_backup/Cc3dSkinSubMeshData.txt
            Cc3dSubMeshData*subMeshData=new Cc3dSubMeshData();
            subMeshData->autorelease();
            subMeshData->init();
            {
                string fullpath=CCFileUtils::sharedFileUtils()->fullPathForFilename((path+"/m_skinMesh_"+numberToStr(skinMeshIndex)+
                                                                                     "/m_skinSubMesh_"+numberToStr(skinSubMeshIndex)+
                                                                                     "/m_subMeshData_backup/Cc3dSkinSubMeshData.txt").c_str());
                //open file
                FILE  *fp=NULL;
                fp=fopen(fullpath.c_str(),"r");//override write
                if(fp==NULL){
                    cout<<"Open "<<fullpath<<" failed!"<<endl;
                    assert(false);
                }
                
                //------------------read file
                //vlist
                vector<Cc3dVector4> t_positionList;
                vector<Cc3dVector2> t_texCoordList;
                vector<Cc3dVector4> t_normalList;
                vector<Cc3dVector4> t_colorList;
                
                int t_nv;
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="m_vlist.size");
                fscanf(fp,"%i",&t_nv);
                for(int i=0;i<t_nv;i++){
                    fskipOneStr(fp,valueOnly);
                    if(!valueOnly)assert(string(tCharBuffer)=="vertex");
                    Cc3dVector4 pos;
                    Cc3dVector2 texCoord;
                    Cc3dVector4 norm;
                    Cc3dVector4 color;
                    float posx,posy,posz;
                    float s,t;
                    float normx,normy,normz;
                    float r,g,b,a;
                    fskipOneStr(fp,valueOnly);
                    fscanf(fp,"%f",&posx);
                    fscanf(fp,"%f",&posy);
                    fscanf(fp,"%f",&posz);
                    fskipOneStr(fp,valueOnly);
                    fscanf(fp,"%f",&s);
                    fscanf(fp,"%f",&t);
                    fskipOneStr(fp,valueOnly);
                    fscanf(fp,"%f",&normx);
                    fscanf(fp,"%f",&normy);
                    fscanf(fp,"%f",&normz);
                    fskipOneStr(fp,valueOnly);
                    fscanf(fp,"%f",&r);
                    fscanf(fp,"%f",&g);
                    fscanf(fp,"%f",&b);
                    fscanf(fp,"%f",&a);
                    //add to list
                    t_positionList.push_back(Cc3dVector4(posx,posy,posz,1));
                    t_texCoordList.push_back(Cc3dVector2(s,t));
                    t_normalList.push_back(Cc3dVector4(normx,normy,normz,0));
                    t_colorList.push_back(Cc3dVector4(r,g,b,a));
                }
                vector<Cc3dIDTriangle> t_IDtriList;
                int t_nIDtri;
                fskipOneStr(fp,valueOnly);
                if(!valueOnly)assert(string(tCharBuffer)=="m_IDtriList.size");
                fscanf(fp,"%i",&t_nIDtri);
                for(int i=0;i<t_nIDtri;i++){
                    fskipOneStr(fp,valueOnly);
                    if(!valueOnly)assert(string(tCharBuffer)=="IDtri");
                    int vID0,vID1,vID2;
                    fscanf(fp,"%i",&vID0);
                    fscanf(fp,"%i",&vID1);
                    fscanf(fp,"%i",&vID2);
                    Cc3dIDTriangle IDtri(vID0,vID1,vID2);
                    //add to list
                    t_IDtriList.push_back(IDtri);
                }
                
                //--------------------------close file
                fclose(fp);
                //----
                subMeshData->m_positionList=t_positionList;
                subMeshData->m_normalList=t_normalList;
                subMeshData->m_texCoordList=t_texCoordList;
                subMeshData->m_colorList=t_colorList;
                subMeshData->m_IDtriList=t_IDtriList;
            }
            //----
            subMesh->setSubMeshData(subMeshData);
            mesh->addSubMesh(subMesh);
           
        }
        //----
         model->addMesh(mesh);
    }
    //----
    actor->setModel(model);
    return actor;

}