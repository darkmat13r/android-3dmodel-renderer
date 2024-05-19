# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("learnopengl")
# Include the Assimp headers
include_directories(third_party)
# Include directories for GLM
include_directories(third_party/glm)
# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
# Gather all source files in the current directory and subdirectories
# Gather all source files from specified directories
# Gather all source files from specified directories
file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/*.cpp"
        "${CMAKE_SOURCE_DIR}/unused/*.cpp"
        "${CMAKE_SOURCE_DIR}/game/*.cpp"
        "${CMAKE_SOURCE_DIR}/math/*.cpp"
        "${CMAKE_SOURCE_DIR}/mesh/*.cpp"
        "${CMAKE_SOURCE_DIR}/shaders/*.cpp"
        "${CMAKE_SOURCE_DIR}/mesh/shader/*.cpp"
        "${CMAKE_SOURCE_DIR}/transform/*.cpp"
        "${CMAKE_SOURCE_DIR}/AndroidJNI/*.cpp"
)

# Print the gathered sources for debugging
message("Source files: ${CMAKE_SOURCE_DIR}")

# Ensure there are source files found
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found.")
endif()

# Add the executable target
add_library(learnopengl SHARED ${SOURCES})


# Specify the path to the shaders
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(SHADER_BINARY_DIR "${CMAKE_BINARY_DIR}/shaders")

# Copy shader files to the build directory
file(GLOB SHADER_FILES "${SHADER_SOURCE_DIR}/*.vert" "${SHADER_SOURCE_DIR}/*.frag")
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${SHADER_BINARY_DIR}/${FILE_NAME} COPYONLY)
endforeach()


# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Specify the path to the prebuilt Assimp library
set(assimp_libs ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libassimp.so)

add_subdirectory(third_party/glm)

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
        glm
)