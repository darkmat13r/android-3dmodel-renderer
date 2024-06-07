//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H


#include <__fwd/string.h>
#include <GLES3/gl3.h>
#include "detail/type_mat4x4.hpp"
#include "math/mat4f.h"

const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 10;

class Shader {
public:

    GLint lightTypeLocation = 0;
    GLint normalAttribute = 0;


    Shader();

    void bind() const;

    void unbind() const;

    void setProjectionMatrix(const Mat4f *projectionMatrix) const;

    GLint getPositionAttrib() const;

    GLint getDiffColorLocation() const;

    GLint getUseDiffTextureLocation() const;

    GLint getUvAttrib() const;

    GLint getAmbientColorLocation() const;

    GLint getAmbientIntensityLocation() const;

    GLint getLightColorLocation() const;

    GLint getSpecularExponentLocation() const;

    GLint getSpecularColorLocation() const;

    GLint getCameraLocalPosLocation() const;

    GLint getLightDirectionLocation() const;

    GLint getDiffuseIntensityLocation() const;

    GLint getNumberOfLightsLocation() const;

    GLint getPointLightColor(int index) const;

    GLint getPointLightAmbientIntensity(int index) const;

    GLint getPointLightDiffuseIntensity(int index) const;

    GLint getPointLightLocalPosition(int index) const;

    GLint getPointLightAttenuationConstant(int index) const;

    GLint getPointLightAttenuationLinear(int index) const;

    GLint getPointLightAttenuationExp(int index) const;


    GLint getNumberOfSpotLightsLocation() const;

    GLint getSpotLightColor(int index) const;

    GLint getSpotLightAmbientIntensity(int index) const;

    GLint getSpotLightDiffuseIntensity(int index) const;

    GLint getSpotLightLocalPosition(int index) const;

    GLint getSpotLightAttenuationConstant(int index) const;

    GLint getSpotLightAttenuationLinear(int index) const;

    GLint getSpotLightAttenuationExp(int index) const;
    GLint getSpotLightDirection(int index) const;
    GLint getSpotLightCutOff(int index) const;


private:
    GLuint program_ = 0;
    GLint projectionMatrixLocation_ = 0;
    GLint positionAttribute_ = 0;
    GLint uvAttribute_ = 0;
    GLint cameraLocalPosLocation_ = 0;
    GLint numberOfPointLightLocation_ = 0;
    GLint numberOfSpotLightLocation_ = 0;

    struct {
        GLint diffuseColor = 0;
        GLint useDiffText_ = 0;
        GLint ambientColor = 0;
        GLint samplerSpecularExponentLocation = 0;
        GLint specularColor = 0;
    } materialLoc;

    struct {
        GLint color = 0;
        GLint ambientIntensity = 0;
        GLint diffuseIntensity = 0;
        GLint direction = 0;
    } lightLoc;

    struct {
        GLint color = 0;
        GLint ambientIntensity = 0;
        GLint diffuseIntensity = 0;
        GLint localPosition = 0;
        struct {
            GLint constant = 1.0;
            GLint linear = 0.0;
            GLint exp = 0.0;
        } attenuation;
    } pointLightLocation[MAX_POINT_LIGHTS];

    struct {
        GLint color = 0;
        GLint ambientIntensity = 0;
        GLint diffuseIntensity = 0;
        GLint localPosition = 0;
        GLint direction = 0;
        GLint cutOff = 0;
        struct {
            GLint constant = 1.0;
            GLint linear = 0.0;
            GLint exp = 0.0;
        } attenuation;
    } spotLightLocation[MAX_SPOT_LIGHTS];

    std::string readFile(std::string &fileName) const;

    static GLuint compileShader(const char *shaderCode, GLenum shaderType);

    bool isValidIndex(int index) const;

    void loadPointLightUniforms();
    void loadSpotLightUniforms();
};


#endif //LEARNOPENGL_SHADER_H
