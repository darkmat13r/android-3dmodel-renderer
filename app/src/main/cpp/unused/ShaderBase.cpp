#include "ShaderBase.h"

#include "../AndroidOut.h"
#include "../Model.h"
#include "../Utility.h"

ShaderBase *ShaderBase::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource,
        const std::string &positionAttributeName,
        const std::string &uvAttributeName,
        const std::string &projectionMatrixUniformName) {
    ShaderBase *shader = nullptr;

    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader) {
        return nullptr;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return nullptr;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            // If we fail to link the shader program, log the result for debugging
            if (logLength) {
                GLchar *log = new GLchar[logLength];
                glGetProgramInfoLog(program, logLength, nullptr, log);
                aout << "Failed to link program with:\n" << log << std::endl;
                delete[] log;
            }

            glDeleteProgram(program);
        } else {
            // Get the attribute and uniform locations by name. You may also choose to hardcode
            // indices with layout= in your shader, but it is not done in this sample
            GLint positionAttribute = glGetAttribLocation(program, positionAttributeName.c_str());
            GLint uvAttribute = glGetAttribLocation(program, uvAttributeName.c_str());
            GLint projectionMatrixUniform = glGetUniformLocation(
                    program,
                    projectionMatrixUniformName.c_str());

            // Only create a new shader if all the attributes are found.
            if (positionAttribute != -1
                && uvAttribute != -1
                && projectionMatrixUniform != -1) {

                shader = new ShaderBase(
                        program,
                        positionAttribute,
                        uvAttribute,
                        projectionMatrixUniform);
            } else {
                glDeleteProgram(program);
            }
        }
    }

    // The shaders are no longer needed once the program is linked. Release their memory.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

GLuint ShaderBase::loadShader(GLenum shaderType, const std::string &shaderSource) {
    Utility::assertGlError();
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        auto *shaderRawString = (GLchar *) shaderSource.c_str();
        GLint shaderLength = shaderSource.length();
        glShaderSource(shader, 1, &shaderRawString, &shaderLength);
        glCompileShader(shader);

        GLint shaderCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

        // If the shader doesn't compile, log the result to the terminal for debugging
        if (!shaderCompiled) {
            GLint infoLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

            if (infoLength) {
                auto *infoLog = new GLchar[infoLength];
                glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
                aout << "Failed to compile with:\n" << infoLog << std::endl;
                delete[] infoLog;
            }

            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

void ShaderBase::activate() const {
    glUseProgram(program_);
}

void ShaderBase::deactivate() const {
    glUseProgram(0);
}

void ShaderBase::drawModel(const Model* model) {
    glBindVertexArray(model->getVAO());
    glDrawElements(GL_TRIANGLES, model->getIndexCount(), GL_UNSIGNED_SHORT, (void *) 0);
    glBindVertexArray(0);
}

void ShaderBase::setProjectionMatrix(Mat4f *projectionMatrix) const {

    glUniformMatrix4fv(projectionMatrix_, 1, GL_TRUE, &projectionMatrix->m[0][0]);
}

void ShaderBase::Prepare(Model *model) {
    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * model->getVertexCount(),
                 model->getVertexData(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(position_);
    glVertexAttribPointer(
            position_,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void *) (0)
    );

    glEnableVertexAttribArray(uv_);
    glVertexAttribPointer(
            uv_,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void *) offsetof(Vertex, uv)
    );


    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(Index) * model->getIndexCount(),
                 model->getIndexData(), GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->getTexture().getTextureID());


    glBindVertexArray(vao);

    // Store VAO, VBO, IBO IDs in the model
    model->setVAO(vao);
    model->setVBO(vbo);
    model->setIBO(ibo);

    Clean();
}

void ShaderBase::Clean() const {
    glBindVertexArray(0);
    glDisableVertexAttribArray(position_);
    glDisableVertexAttribArray(uv_);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
