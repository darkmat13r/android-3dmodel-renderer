#version 300 es
precision mediump float;

in vec2 fragUV;
in vec3 normal0;

struct Material {
    vec3 diffuseColor;
    vec3 ambientColor;
    bool useTexture;
};

struct Light {
    vec3 color;
    float ambientIntensity;
    uint type;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D uTexture;
uniform Material uMaterial;
uniform Light uLight;

out vec4 outColor;

void main() {
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);
    if (uMaterial.useTexture) {
        vec4 textureColor = texture(uTexture, fragUV);
        finalColor = textureColor;
    } else {
        finalColor = vec4(uMaterial.diffuseColor, 1.0);
    }

    vec3 ambientColor = uMaterial.ambientColor * uLight.color * uLight.ambientIntensity;
    vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 1.0);


    outColor = finalColor * vec4(ambientColor, 1.0) + diffuseColor;
}
