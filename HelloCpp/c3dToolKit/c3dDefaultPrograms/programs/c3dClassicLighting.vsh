//attribute
attribute vec4 a_position;
attribute vec4 a_normal;
attribute vec2 a_texCoord;
attribute vec4 a_color;


//uniform
uniform mat4 modelMat;
uniform mat4 normalMat;
uniform vec4 lightPos_world;
uniform vec4 eyePos_world;
uniform vec4 diffuseMaterial;
uniform vec4 diffuseLight;
uniform vec4 ambientMaterial;
uniform vec4 ambientLight;
uniform vec4 specularMaterial;
uniform vec4 specularLight;
uniform float shininess;

//varying (pass to fragment shader)
varying vec4 mainColor;
varying vec4 secondaryColor;
varying vec2 texCoordOut;



void main(void) {
    vec4 diffuseML=vec4(vec3(diffuseMaterial)*vec3(diffuseLight),diffuseMaterial.a);
    vec4 ambientML=vec4(vec3(ambientMaterial)*vec3(ambientLight),0);
    vec4 specularML=vec4(vec3(specularMaterial)*vec3(specularLight),0);
    //----get normal in world space
    //if scaling is uniformed, we can use modelMat instead of normalMat
    //if no scaling, we need not normalization
    vec3 norm_world = normalize(vec3(normalMat*a_normal));
    //----get pos in world space
    vec3 pos_world = vec3(modelMat*a_position);
    //----lightPos already in world space
    //----calculate diffuse color
    vec3 posToLight=vec3(normalize(vec3(lightPos_world)-pos_world));
    float normDotPosToLight = max(0.0, dot(norm_world, posToLight));
    vec3 diffuseColor= normDotPosToLight*vec3(diffuseML);
    //----calculate ambient color
    //vec3(ambientML);
    //----calculate specular color
    vec3 posToEye=normalize(vec3(eyePos_world)-pos_world);
    vec3 halfVector=(posToLight+posToEye)*0.5;
    float normDotHalfVector=max(0.0,dot(norm_world, halfVector));
    float pf=normDotHalfVector==0.0?0.0:pow(normDotHalfVector,shininess);
    vec3 specularColor= pf*vec3(specularML);
    //----set varying
    //the final alpha is equal to diffuseML.a(and is equal to diffuse_material.a)
    mainColor = vec4(vec3(ambientML)+diffuseColor*vec3(a_color),diffuseML.a*a_color.a);
    float secondaryColorAlpha=pf;
    secondaryColor=vec4(specularColor,secondaryColorAlpha);
    gl_Position = CC_MVPMatrix * a_position;
    texCoordOut = a_texCoord;

}
