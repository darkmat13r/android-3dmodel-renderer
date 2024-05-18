# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("learnopengl")
# Include the Assimp headers
include_directories(third_party)
# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(learnopengl SHARED
        main.cpp
        AndroidOut.cpp
        Renderer.cpp
        Shader.cpp
        Model.h
        game/GameObject.cpp
        game/Scene.cpp
        math/quaternion.cpp
        math/vector3.cpp
        math/mat4f.cpp
        game/Camera.cpp
        transform/Transform.cpp
        AndroidJNI/AndroidJNIIOSystem.cpp
        AndroidJNI/BundledAssetIOSystem.cpp
        TextureAsset.cpp
        Utility.cpp)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Specify the path to the prebuilt Assimp library
set(assimp_libs ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libassimp.so)

# Configure libraries CMake uses to link your target library.
target_link_libraries(learnopengl
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log
        # Assimp library
        ${assimp_libs}
)