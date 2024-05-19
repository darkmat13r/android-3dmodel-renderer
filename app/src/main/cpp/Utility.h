#ifndef ANDROIDGLINVESTIGATIONS_UTILITY_H
#define ANDROIDGLINVESTIGATIONS_UTILITY_H

#include <cassert>
#include "math/quaternion.h"
#include "math/mat4f.h"

class Utility {
public:
    static bool checkAndLogGlError(bool alwaysLog = false);

    static inline void assertGlError() { assert(checkAndLogGlError()); }

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

#endif //ANDROIDGLINVESTIGATIONS_UTILITY_H