

varying mediump vec2 v_texCoord;
varying lowp vec4 v_fragmentColor;
uniform sampler2D CC_Texture0;

void main()
{
    gl_FragColor =  texture2D(CC_Texture0, v_texCoord)*v_fragmentColor;
}
