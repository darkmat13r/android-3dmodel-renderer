#version 300 es
precision mediump float;

in vec2 fragUV;
in vec3 normal0;
in vec3 localPos0;

struct Material {
    vec3 diffuseColor;
    vec3 ambientColor;
    vec3 specularColor;
    bool useTexture;
};

struct Light {
    vec3 color;
    float ambientIntensity;
    float type;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D uTexture;
uniform sampler2D uSpecTexture;
uniform Material uMaterial;
uniform Light uLight;
uniform vec3 uCameraLocalPos;

out vec4 outColor;

void main() {
    vec4 finalColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);

    if (uMaterial.useTexture) {
        vec4 textureColor = texture(uTexture, fragUV);
        finalColor = textureColor;
    }

    vec3 ambientColor = uMaterial.ambientColor * uLight.color * uLight.ambientIntensity;

    vec3 Normal = normalize(normal0);

    if (uLight.type == 1.0) {
        float diffuseFactor = max(dot(Normal, normalize(uLight.direction)), 0.0);
        if(diffuseFactor > 0.0){

            diffuseColor = vec4(uLight.color, 1.0) * uLight.diffuseIntensity  * diffuseFactor * vec4(uMaterial.diffuseColor, 1.0);

            vec3 pixelToCamera  = normalize(uCameraLocalPos - localPos0);
            vec3 lightReflect = normalize(reflect(uLight.direction , Normal));

            float specularFactor = dot(pixelToCamera, lightReflect);
            if(specularFactor > 0.0){
                float specularExponent = texture(uSpecTexture, fragUV).r * 255.0;
                specularFactor = pow(specularFactor, specularExponent);
                specularColor = vec4(uLight.color , 1.0) * vec4(uMaterial.specularColor, 1.0) * specularFactor;
            }


        }
    }else{
        diffuseColor =  vec4(uMaterial.diffuseColor, 1.0);
    }

    outColor = finalColor * clamp((vec4(ambientColor, 1.0) + diffuseColor + specularColor), 0.0, 1.0 );
}
