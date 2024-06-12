#version 300 es
precision mediump float;
const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 10;
in vec2 fragUV;
in vec3 normal0;
in vec3 localPos0;
in vec3 tangent0;
in vec3 worldPos0;

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

struct DirectionalLight {
    Light light;
    vec3 direction;
};

struct Attenuation {
    float constant;
    float linear;
    float exp;
};
struct PointLight {
    Light light;
    Attenuation atten;
    vec3 localPos;
};

struct SpotLight {
    PointLight pointLight;
    vec3 direction;
    float cutOff;
};


uniform sampler2D uTexture;
uniform sampler2D uSpecTexture;
uniform sampler2D uNormalTexture;
uniform Material uMaterial;
uniform DirectionalLight uLight;
uniform int uNumOfLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform int uNumOfSpotLights;
uniform SpotLight uSpotLights[MAX_SPOT_LIGHTS];
uniform vec3 uCameraLocalPos;

out vec4 outColor;

vec3 calculateBumpedNormal(){
    vec3 normal = normalize(normal0);
    vec3 tangent = normalize(tangent0);
    tangent = normalize(tangent - dot(tangent, normal) * normal);
    vec3 biTangent = cross(tangent, normal);
    vec3 bumpedNormal = texture(uNormalTexture, fragUV).xyz;
    bumpedNormal = 2.0 * bumpedNormal - vec3(1.0, 1.0,1.0);
    vec3 newNormal;
    mat3 tbn = mat3(tangent, biTangent, normal);
    newNormal = tbn * bumpedNormal;
    newNormal = normalize(newNormal);
    return newNormal;

}

vec4 calculateLightInternal(Light light, vec3 direction, vec3 normal) {

    vec3 ambientColor = uMaterial.ambientColor * light.color * light.ambientIntensity;

    vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);
    float diffuseFactor = max(dot(normal, normalize(direction)), 0.0);

    if (diffuseFactor > 0.0) {
        diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * diffuseFactor * vec4(uMaterial.diffuseColor, 1.0);
        vec3 pixelToCamera = normalize(uCameraLocalPos - localPos0);
        vec3 lightReflect = normalize(reflect(direction, normal));
        float specularFactor = dot(pixelToCamera, lightReflect);
        if (specularFactor > 0.0) {
            float specularExponent = texture(uSpecTexture, fragUV).r * 255.0;
            specularFactor = pow(specularFactor, specularExponent);
            specularColor = vec4(light.color, 1.0) * vec4(uMaterial.specularColor, 1.0) * specularFactor;
        }
    }

    vec4 color = clamp((vec4(ambientColor, 1.0) + diffuseColor + specularColor), 0.0, 1.0);
    return color;
}

vec4 calculateDirectionalLight(vec3 normal) {
    vec4 color = calculateLightInternal(uLight.light, uLight.direction, normal);
    return color;
}

vec4 calculatePointLight(PointLight pointLight, vec3 normal) {
    vec3 direction = localPos0 - pointLight.localPos;
    float distance = length(direction);
    direction = normalize(direction);
    vec4 color = calculateLightInternal(pointLight.light, direction, normal);
    float attenuation = pointLight.atten.constant + pointLight.atten.linear * distance + pointLight.atten.exp * distance * distance;

    return color / attenuation;
}

vec4 calculateSpotLight(SpotLight spotLight, vec3 normal) {
    vec3 lightToPixel = normalize(localPos0 - spotLight.pointLight.localPos);
    float spotLightFactor = dot(lightToPixel, spotLight.direction);
    if(spotLightFactor > spotLight.cutOff){
        vec4 color = calculatePointLight(spotLight.pointLight, normal);
        float spotLightIntensity = (1.0 - (1.0 - spotLightFactor)/ (1.0 - cos(spotLight.cutOff)));
        return color * spotLightIntensity;
    }
    return vec4(0.0, 0.0, 0.0, 0.0);
}

void main() {

    vec4 textureColor = texture(uTexture, fragUV);
    vec3 normal = calculateBumpedNormal();

    vec4 totalLight = calculateDirectionalLight(normal);
    for (int i = 0; i < uNumOfLights; i++) {
        totalLight += calculatePointLight(uPointLights[i], normal);
    }

    for (int i = 0; i < uNumOfSpotLights; i++) {
        totalLight += calculateSpotLight(uSpotLights[i], normal);
    }

    outColor = textureColor * totalLight;

}
