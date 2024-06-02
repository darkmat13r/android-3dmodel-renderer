#version 300 es
in vec3 inPosition;
in vec2 inUV;
in vec3 inNormal;

out vec2 fragUV;
out vec3 normal0;
out vec3 localPos0;

uniform mat4 uProjection;

void main() {
    fragUV = inUV;
    gl_Position = uProjection * vec4(inPosition, 1.0);
    normal0 = inNormal;
    localPos0 = inPosition;
}