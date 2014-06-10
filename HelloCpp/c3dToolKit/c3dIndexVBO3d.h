#ifndef __HelloCpp__c3dIndexVBO__
#define __HelloCpp__c3dIndexVBO__
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "c3dDefine.h"
#include "c3dCommonFunc.h"
class Cc3dIndexVBO3d:public CCObject
{
public:
	Cc3dIndexVBO3d(){
		m_posBuffer=0 ;
		m_texCoordBuffer=0 ;
        m_normalBuffer=0;
        m_colorBuffer=0;
		m_indexBuffer=0;
		m_indexArrayLen=0;
	    m_posArrayLen=0;
	    m_texCoordArrayLen=0;
        m_normalArrayLen=0;
        m_colorArrayLen=0;
	}
	virtual ~Cc3dIndexVBO3d(){
		if(m_posBuffer!=0)glDeleteBuffers(1, &m_posBuffer) ;
		if(m_texCoordBuffer!=0)glDeleteBuffers(1, &m_texCoordBuffer) ;
        if(m_normalBuffer!=0)glDeleteBuffers(1, &m_normalBuffer) ;
        if(m_colorBuffer!=0)glDeleteBuffers(1, &m_colorBuffer) ;
		if(m_indexBuffer!=0)glDeleteBuffers(1, &m_indexBuffer) ;
	}
    static Cc3dIndexVBO3d*create(){
        Cc3dIndexVBO3d*p=createAutoreleasedObject(p);
        return p;
    }
    bool init();
    static void enableAttribArray_position(bool isEnable);
	static void enableAttribArray_texCoord(bool isEnable);
	static void enableAttribArray_normal(bool isEnable);
	static void enableAttribArray_color(bool isEnable);
	static bool isEnabledAttribArray_position();
	static bool isEnabledAttribArray_texCoord();
	static bool isEnabledAttribArray_normal();
	static bool isEnabledAttribArray_color();
    static void bindTexture(GLuint textureUnit, GLuint textureId);
	void submitPosition(const float posArray[],const int posArrayLen,GLenum usage);
	void submitTexCoord(const float texCoordArray[],const int texCoordArrayLen,GLenum usage);
    void submitNormal(const float normalArray[],const int normalArrayLen,GLenum usage);
    void submitColor(const float colorArray[],const int colorArrayLen,GLenum usage);
	void submitIndex(const short indexArray[],const int indexArrayLen,GLenum usage);
	void setPointers();
	void draw(GLenum mode);
protected:
    void genBuffers();
protected:
    GLuint m_posBuffer;
    GLuint m_texCoordBuffer;
    GLuint m_normalBuffer;
    GLuint m_colorBuffer;
    GLuint m_indexBuffer;
	int m_indexArrayLen;
	int m_posArrayLen;
	int m_texCoordArrayLen;
    int m_normalArrayLen;
    int m_colorArrayLen;

};
#endif /* defined(__HelloCpp__c3dIndexVBO__) */