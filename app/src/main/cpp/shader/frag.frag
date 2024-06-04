#version 300 es
precision mediump float;
const int MAX_POINT_LIGHTS = 2;
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

};

struct DirectionalLight{
    Light light;
    vec3 direction;
};

struct Attenuation{
    float constant;
    float linear;
    float exp;
};
struct PointLight{
    Light light;
    Attenuation atten;
    vec3 localPos;
};


uniform sampler2D uTexture;
uniform sampler2D uSpecTexture;
uniform Material uMaterial;
uniform DirectionalLight uLight;
uniform int uNumOfLights;
uniform PointLight uPointLight[MAX_POINT_LIGHTS];
uniform vec3 uCameraLocalPos;

out vec4 outColor;

vec4 calculateDirectionalLight(vec3 normal){
    vec4 color =  calculateLightInternal(uLight.light, uLight.direction, normal);
    return color;
}

vec4 calculateLightInternal(Light light, vec3 direction, vec3 normal){

    vec3 ambientColor = uMaterial.ambientColor * light.color * light.ambientIntensity;

    vec4 diffuseColor = vec4(uMaterial.diffuseColor, 1.0);
    vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);
    float diffuseFactor = max(dot(normal, normalize(direction)), 0.0);

    if (diffuseFactor > 0.0){
        diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity  * diffuseFactor * vec4(uMaterial.diffuseColor, 1.0);
        vec3 pixelToCamera  = normalize(uCameraLocalPos - localPos0);
        vec3 lightReflect = normalize(reflect(direction, normal));
        float specularFactor = dot(pixelToCamera, lightReflect);
        if (specularFactor > 0.0){
            float specularExponent = texture(uSpecTexture, fragUV).r * 255.0;
            specularFactor = pow(specularFactor, specularExponent);
            specularColor = vec4(light.color, 1.0) * vec4(uMaterial.specularColor, 1.0) * specularFactor;
        }
    }

    vec4 color =  clamp((vec4(ambientColor, 1.0) + diffuseColor + specularColor), 0.0, 1.0);
    return color;
}

vec4 calculatePointLight(int index, vec3 normal){
    vec3 direction = localPos0 - uPointLight[index].localPos;
    float distance = length(direction);
    direction = normalize(direction);
    vec4 color = calculateLightInternal(uPointLight[index].light, direction, normal);
    float attenuation = uPointLight[index].atten.constant + uPointLight[index].atten.linear * distance + uPointLight[index].atten.exp * distance * distance;

    return color/attenuation;
}

void main() {

    vec4 textureColor = texture(uTexture, fragUV);
    vec3 normal  = normalize(normal0);

    vec4 totalLight = calculateDirectionalLight(normal);
    for (int i = 0; i < uNumOfLights; i++){
        totalLight += calculatePointLight(i, normal);
    }

    outColor = textureColor * totalLight;

}
