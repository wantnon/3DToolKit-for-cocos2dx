//varying (passed from vertex shader)
varying lowp vec4 v_mainColor;
varying lowp vec4 v_secondaryColor;
varying mediump vec2 v_texCoord;


//sampler uniform
uniform sampler2D CC_Texutre0;

void main(void) {
    gl_FragColor = v_mainColor * texture2D(CC_Texutre0, v_texCoord)+v_secondaryColor;
}
