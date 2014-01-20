
#ifdef GL_ES	
varying mediump vec2 v_texCoord;
varying lowp vec4 v_fragmentColor;
#else
varying  vec2 v_texCoord;
varying  vec4 v_fragmentColor;
#endif

uniform  sampler2D CC_Texture0;

void main()
{
    gl_FragColor =  texture2D(CC_Texture0, v_texCoord)*v_fragmentColor;
}
