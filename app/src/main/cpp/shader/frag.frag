#version 300 es
precision mediump float;

in vec2 fragUV;

struct Material{
    vec3 diffuseColor;
    vec3 ambientColor;
    bool useTexture;
};

struct Light{
    vec3 color;
    float ambientIntensity;
};

uniform sampler2D uTexture;
uniform Material uMaterial;
uniform Light uLight;

out vec4 outColor;

void main() {
    vec4 finalColor = vec4(0.0,0.0, 0.0, 1.0);
    if(uMaterial.useTexture){
        vec4 textureColor  = texture(uTexture, fragUV);
        finalColor =  textureColor;
    }else{
        finalColor =  vec4(uMaterial.diffuseColor, 1.0);
    }
    vec3 lightColor = uMaterial.ambientColor * uLight.color * uLight.ambientIntensity;
    outColor = finalColor * vec4(lightColor, 1.0);
}