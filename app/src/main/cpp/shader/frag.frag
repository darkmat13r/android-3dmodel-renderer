#version 300 es
precision mediump float;

in vec2 fragUV;

struct Material{
    vec4 diffuseColor;
    vec4 ambientColor;
    bool useTexture;
};

struct Light{
    vec4 color;
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
        finalColor =  uMaterial.diffuseColor;
    }
    outColor = finalColor * uMaterial.ambientColor * uLight.color * uLight.ambientIntensity;
}