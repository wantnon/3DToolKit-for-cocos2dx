//varying (passed from vertex shader)
varying lowp vec4 mainColor;
varying lowp vec4 secondaryColor;
varying mediump vec2 texCoordOut;

//sampler uniform
uniform sampler2D CC_Texutre0;

void main(void) {
    gl_FragColor = mainColor * texture2D(CC_Texutre0, texCoordOut)+secondaryColor;
}
