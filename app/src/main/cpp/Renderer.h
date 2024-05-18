#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>

#include "Model.h"
#include "game/GameObject.h"
#include "unused/ShaderBase.h"
#include "math/mat4f.h"
#include "game/Scene.h"
#include "game/Camera.h"
#include "mesh/shader/Shader.h"

struct android_app;


class Renderer {
public:
    /*!
     * @param pApp the android_app this Renderer belongs to, needed to configure GL
     */
    inline Renderer(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0),
            scene_(),
            shaderNeedsNewProjectionMatrix_(true),
            projectionMatrix(
                    Mat4f::Identity()
            ) {
        initScene();
        initRenderer();
    }

    virtual ~Renderer();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();
    void initScene();

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initRenderer();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    /*!
     * Creates the models for this sample. You'd likely load a scene configuration from a file or
     * use some other setup logic in your full game.
     */
    void createModels();

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;
    float rotation = 0;
    float scale = 0;
    float translation = -2;
    float delta = 0.01;

    float isMoving = false;
    float lastX = 0;
    float lastY = 0;

    bool shaderNeedsNewProjectionMatrix_;

    std::unique_ptr<Shader> shader_;
    std::unique_ptr<Scene> scene_;
    std::unique_ptr<Mat4f> projectionMatrix;
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H