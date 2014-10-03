//
//  c3dProgram.h
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-1.
//
//

#ifndef __HelloCpp__c3dProgram__
#define __HelloCpp__c3dProgram__
#include "cocos2d.h"
using namespace cocos2d;
#include <iostream>
#include <string>
#include <map>
using namespace std;
#include <iostream>
#include "c3dDefine.h"
#include "c3dCommonFunc.h"
//if program1 and program2 have a uniform variable with the same name, the two variable's uniform ID should be different.
//so good way is let each shader program hold his own uniform IDs.
class Cc3dProgram:public CCGLProgram
{
public:
    Cc3dProgram(){
	}
	virtual ~Cc3dProgram(){
	}
public:
    
    bool init(){return true;}
    bool init(string vertFileName,string fragFileName);
    void attachUniform(string unifoName);
    void passUnifoValue1f(string unifoName,GLfloat v);
    void passUnifoValue1i(string unifoName,GLint v);
    void passUnifoValueMatrixNfv(string unifoName,const GLfloat *array,int arrayLen);
    void passUnifoValueNfv(string unifoName,const GLfloat *array,int arrayLen);
    void passUnifoValueNiv(string unifoName,const GLint *array,int arrayLen);
    void passUnifoValueMatrixNfv(string unifoName,const vector<GLfloat>&valueList);
    void passUnifoValueNfv(string unifoName,const vector<GLfloat>&valueList);
    void passUnifoValueNiv(string unifoName,const vector<GLint>&valueList);
    void setName(const string&name){m_name=name;}
    string getName()const{return m_name;};
protected:
	map<string,GLint> m_unifoMap;
    string m_name;
    
};

#endif /* defined(__HelloCpp__c3dProgram__) */
