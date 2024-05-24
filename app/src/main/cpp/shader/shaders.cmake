# Read the vertex shader file
file(READ "${CMAKE_SOURCE_DIR}/shader/vert.vert" VERT_SHADER_SOURCE)
string(REPLACE "\n" "\\n" VERT_SHADER_SOURCE "${VERT_SHADER_SOURCE}")
string(REPLACE "\"" "\\\"" VERT_SHADER_SOURCE "${VERT_SHADER_SOURCE}")

# Read the fragment shader file
file(READ "${CMAKE_SOURCE_DIR}/shader/frag.frag" FRAG_SHADER_SOURCE)
string(REPLACE "\n" "\\n" FRAG_SHADER_SOURCE "${FRAG_SHADER_SOURCE}")
string(REPLACE "\"" "\\\"" FRAG_SHADER_SOURCE "${FRAG_SHADER_SOURCE}")

# Configure the header file with embedded shaders
configure_file(
        "${CMAKE_SOURCE_DIR}/shader/Shaders.h.in"
        "${CMAKE_BINARY_DIR}/shader/Shaders.h"
        @ONLY
)

