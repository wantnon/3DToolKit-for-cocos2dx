#include"c3dIndexVBO3d.h"
bool Cc3dIndexVBO3d::init(){
    genBuffers();
    return true;
}

void Cc3dIndexVBO3d::enableAttribArray_position(bool isEnable){
	if(isEnable)
		glEnableVertexAttribArray(kCCVertexAttrib_Position);
	else
		glDisableVertexAttribArray(kCCVertexAttrib_Position);
}
void Cc3dIndexVBO3d::enableAttribArray_texCoord(bool isEnable){
	if(isEnable)
		glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
	else
		glDisableVertexAttribArray(kCCVertexAttrib_TexCoords);
}
void Cc3dIndexVBO3d::enableAttribArray_normal(bool isEnable){
	if(isEnable)
		glEnableVertexAttribArray(kCCVertexAttrib_Normals);
	else
		glDisableVertexAttribArray(kCCVertexAttrib_Normals);
}
void Cc3dIndexVBO3d::enableAttribArray_color(bool isEnable){
	if(isEnable)
		glEnableVertexAttribArray(kCCVertexAttrib_Color);
	else
		glDisableVertexAttribArray(kCCVertexAttrib_Color);
}


bool Cc3dIndexVBO3d::isEnabledAttribArray_position(){
	GLint isEnabled;
	glGetVertexAttribiv(kCCVertexAttrib_Position,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&isEnabled);
	return (bool)isEnabled;
}
bool Cc3dIndexVBO3d::isEnabledAttribArray_texCoord(){
	GLint isEnabled;
	glGetVertexAttribiv(kCCVertexAttrib_TexCoords,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&isEnabled);
	return (bool)isEnabled;
}
bool Cc3dIndexVBO3d::isEnabledAttribArray_normal(){
	GLint isEnabled;
	glGetVertexAttribiv(kCCVertexAttrib_Normals,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&isEnabled);
	return (bool)isEnabled;
}
bool Cc3dIndexVBO3d::isEnabledAttribArray_color(){
	GLint isEnabled;
	glGetVertexAttribiv(kCCVertexAttrib_Color,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&isEnabled);
	return (bool)isEnabled;
}
void Cc3dIndexVBO3d::genBuffers(){
    if(m_posBuffer==0)glGenBuffers(1, &m_posBuffer);
    if(m_texCoordBuffer==0)glGenBuffers(1, &m_texCoordBuffer);
    if(m_normalBuffer==0)glGenBuffers(1, &m_normalBuffer);
    if(m_colorBuffer==0)glGenBuffers(1, &m_colorBuffer);
    if(m_indexBuffer==0)glGenBuffers(1, &m_indexBuffer);
}
void Cc3dIndexVBO3d::submitPosition(const float *posArray,const int posArrayLen,GLenum usage){
    m_posArrayLen=posArrayLen;
    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_posArrayLen*sizeof(float), posArray, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Cc3dIndexVBO3d::submitTexCoord(const float *texCoordArray,const int texCoordArrayLen,GLenum usage){
    m_texCoordArrayLen=texCoordArrayLen;
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_texCoordArrayLen*sizeof(float), texCoordArray, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Cc3dIndexVBO3d::submitNormal(const float *normalArray,const int normalArrayLen,GLenum usage){
    m_normalArrayLen=normalArrayLen;
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_normalArrayLen*sizeof(float), normalArray, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Cc3dIndexVBO3d::submitColor(const float colorArray[],const int colorArrayLen,GLenum usage){
    m_colorArrayLen=colorArrayLen;
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorArrayLen*sizeof(float), colorArray, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Cc3dIndexVBO3d::submitIndex(const short *indexArray,const int indexArrayLen,GLenum usage){
    m_indexArrayLen=indexArrayLen;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexArrayLen*sizeof(short), indexArray, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Cc3dIndexVBO3d::setPointers(){
    //set position format
    glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer);
    glVertexAttribPointer(kCCVertexAttrib_Position, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //set texCoord format
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //set normal format
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glVertexAttribPointer(kCCVertexAttrib_Normals, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //set color format
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
void Cc3dIndexVBO3d::draw(GLenum mode){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    //GL_UNSIGNED_SHORT, see: http://user.qzone.qq.com/350479720/blog/1386772563
    glDrawElements(mode, m_indexArrayLen, GL_UNSIGNED_SHORT, 0) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_GL_ERROR_DEBUG();
}
void Cc3dIndexVBO3d::bindTexture(GLuint textureUnit, GLuint textureId){
    ccGLBindTexture2DN(textureUnit,textureId);
    glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
    
}