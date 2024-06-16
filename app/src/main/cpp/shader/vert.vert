#version 300 es
in vec3 inPosition;
in vec2 inUV;
in vec3 inNormal;
in vec3 inTangent;

out vec2 fragUV;
out vec3 normal0;
out vec3 localPos0;
out vec3 tangent0;
out vec3 worldPos0;

uniform mat4 uProjection;
uniform mat4 uModelProjection;

void main() {
    fragUV = inUV;
    gl_Position = uProjection * vec4(inPosition, 1.0);
    localPos0 = inPosition;
    normal0 = (uModelProjection * vec4(inNormal, 0.0)).xyz;
    tangent0 = (uModelProjection * vec4(inTangent, 0.0)).xyz;
    worldPos0 = (uModelProjection * vec4(inPosition, 1.0)).xyz;
}