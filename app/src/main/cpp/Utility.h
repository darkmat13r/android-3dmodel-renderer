#ifndef ANDROIDGLINVESTIGATIONS_UTILITY_H
#define ANDROIDGLINVESTIGATIONS_UTILITY_H

#include <cassert>
#include <GLES3/gl3.h>
#include "math/quaternion.h"
#include "math/mat4f.h"
#include "AndroidOut.h"

#define CHECK_ERROR(e) case e: aout << "GL Error: "#e << " at " << file << ":" << line << " in function " << func << std::endl; break;

class Utility {
public:
    static inline bool checkAndLogGlError(const char* file, const char* func, int line, bool alwaysLog = false) {
        GLenum error = glGetError();
        if (error == GL_NO_ERROR) {
            if (alwaysLog) {
                aout << "No GL error in " << file << ":" << line << " in function " << func << std::endl;
            }
            return true;
        } else {
            switch (error) {
                CHECK_ERROR(GL_INVALID_ENUM);
                CHECK_ERROR(GL_INVALID_VALUE);
                CHECK_ERROR(GL_INVALID_OPERATION);
                CHECK_ERROR(GL_INVALID_FRAMEBUFFER_OPERATION);
                CHECK_ERROR(GL_OUT_OF_MEMORY);
                default:
                    aout << "Unknown GL error: " << error << " at " << file << ":" << line << " in function " << func << std::endl;
            }
            return false;
        }
    }

    static inline void assertGlError(const char* file, const char* func, int line) {
        assert(checkAndLogGlError(file, func, line));
    }

    /**
     * Generates an orthographic projection matrix given the half height, aspect ratio, near, and far
     * planes
     *
     * @param outMatrix the matrix to write into
     * @param halfHeight half of the height of the screen
     * @param aspect the width of the screen divided by the height
     * @param near the distance of the near plane
     * @param far the distance of the far plane
     * @return the generated matrix, this will be the same as @a outMatrix so you can chain calls
     *     together if needed
     */
    static Mat4f *
    buildPerspectiveMat(Mat4f *outMatrix, float halfHeight, float aspect, float near,
                        float far);

    static float *buildIdentityMatrix(float *outMatrix);


    static Mat4f *
    buildOrthographicMatrix(Mat4f *outMatrix, float halfHeight, float aspect, float near,
                            float far);
};

#define CHECK_GL_ERROR() Utility::checkAndLogGlError(__FILE__, __FUNCTION__, __LINE__)
#define ASSERT_GL_ERROR() Utility::assertGlError(__FILE__, __FUNCTION__, __LINE__)

#endif //ANDROIDGLINVESTIGATIONS_UTILITY_H
