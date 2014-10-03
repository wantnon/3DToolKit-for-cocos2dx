//
//  c3dSimpleModelLoader.h
//  HelloCpp
//
//  Created by apple on 14-10-3.
//
//

#ifndef __HelloCpp__c3dSimpleModelLoader__
#define __HelloCpp__c3dSimpleModelLoader__

#include <iostream>
using namespace std;
#include "c3dActor.h"

static char tCharBuffer[1024]={0};
static void fskipOneStr(FILE * fp,bool valueOnly){
	assert(fp);
	if(valueOnly==false){
		fscanf(fp,"%s",tCharBuffer);
	}
}
static void fprintKey(FILE * fp,bool valueOnly,const string&key){
	assert(fp);
	if(valueOnly==false){
		fprintf(fp,"%s",key.c_str());
	}
}
static Cc3dVector4 fscanVector4(FILE * fp){
	assert(fp);
	float arr[4];
	for(int i=0;i<4;i++){
		fscanf(fp,"%f",&arr[i]);
	}
	return Cc3dVector4(arr);
}

Cc3dActor* c3dSimpleLoadActor(string path);
#endif /* defined(__HelloCpp__c3dSimpleModelLoader__) */
