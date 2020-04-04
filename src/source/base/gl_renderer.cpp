#include "base/gl_renderer.h"
#include <iostream>

#include "base/gl.h"
#include "base/context.h"

namespace APC
{
    GLRenderer::GLRenderer()
        : m_height( 0 )
        , m_width( 0 )
    {
    }

    void GLRenderer::init(int w, int h)
    {
        m_width = w;
        m_height = h;
        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glViewport(0, 0, w, h);
        m_texture = APC::Context::getInstance().getResource<APC::GLTextureResource>( "Law-abidingAfricanAmerican.png" );

#ifdef GLES2
        const GLchar* fragmentShaderSource = "#version 300 es\n"
                                           "precision mediump float;\n"
                                           "in vec3 ourColor;\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D ourTexture;\n"
                                           "void main()\n"
                                           "{\n"
                                           "color = texture(ourTexture, TexCoord);\n"
                                           "}\0\n";
        const GLchar* vertexShaderSource = "#version 300 es\n"
                                            "layout (location = 0) in vec3 position;\n"
                                            "layout (location = 1) in vec3 color;\n"
                                            "layout (location = 2) in vec2 texCoord;\n"
                                            "out vec3 ourColor;\n"
                                            "out vec2 TexCoord;\n"
                                            "void main()\n"
                                            "{\n"
                                            "gl_Position = vec4(position, 1.0f);\n"
                                            "ourColor = color;\n"
                                            "TexCoord = texCoord;\n"
                                            "}\0";
#else
        const GLchar* fragmentShaderSource = "#version 330 core\n"
                                           "in vec3 ourColor;\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D ourTexture;\n"
                                           "void main()\n"
                                           "{\n"
                                           "color = texture(ourTexture, TexCoord);\n"
                                           "}\0\n";
        const GLchar* vertexShaderSource = "#version 330 core\n"
                                             "layout (location = 0) in vec3 position;\n"
                                             "layout (location = 1) in vec3 color;\n"
                                             "layout (location = 2) in vec2 texCoord;\n"
                                             "out vec3 ourColor;\n"
                                             "out vec2 TexCoord;\n"
                                             "void main()\n"
                                             "{\n"
                                             "gl_Position = vec4(position, 1.0f);\n"
                                             "ourColor = color;\n"
                                             "TexCoord = texCoord;\n"
                                             "}\0";
#endif

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);


        // Check for compile time errors
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            APC::Context::getInstance().log( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" );
            APC::Context::getInstance().log( infoLog );
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);


        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            APC::Context::getInstance().log( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" );
            APC::Context::getInstance().log( infoLog );
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // Check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            APC::Context::getInstance().log( "ERROR::SHADER::shaderProgram::LINKING_FAILED\n" );
            APC::Context::getInstance().log( infoLog );
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

//        GLfloat vertices[] = {
//                // Positions          // Colors           // Texture Coords
//                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
//        };

        GLfloat vertices[] = {
                // Positions          // Colors           // Texture Coords
                1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Top Right
                1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // Bottom Right
                -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Bottom Left
                -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f  // Top Left
        };

        GLshort indices[] = {  // Note that we start from 0!
                0, 1, 3, // First Triangle
                1, 2, 3  // Second Triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // TexCoord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
    }

    void GLRenderer::draw()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram( shaderProgram );

        glBindVertexArray(VAO);
//
        glBindTexture(GL_TEXTURE_2D, m_texture->getIndex() );
//        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), m_texture->getIndex() );

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

    void GLRenderer::destroy()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    int GLRenderer::getWidth()
    {
        return m_width;
    }

    int GLRenderer::getHeigth()
    {
        return m_height;
    }
}