#include "gl_renderer.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl.h"
#include "apc/context.h"
#include "apc/transform.h"

namespace apc
{
    GLRenderer::GLRenderer()
        : m_height( 0 )
        , m_width( 0 )
        , m_hratio( 0.0f )
        , m_wratio( 0.0f )
        , m_shaderProgram( 0 )
        , m_renderTextureShaderProgram( 0 )
        , m_frameBuffer( 0 )
        , m_renderTexture( 0 )
        , VBO( 0 )
        , VAO( 0 )
        , EBO( 0 )
        , m_proportionWidth( 0.0f )
        , m_proportionHeight( 0.0f )
    {
    }

    void GLRenderer::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

#ifdef GLES2
        const GLchar* fragmentShaderSource = "#version 300 es\n"
                                           "precision mediump float;\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D mainTexture;\n"
                                           "uniform vec4 colorFactor;\n"
                                           "void main()\n"
                                           "{\n"
                                                "color = texture(mainTexture, TexCoord) * colorFactor;\n"
                                           "}\0";

        const GLchar* vertexShaderSource = "#version 300 es\n"
                                            "layout (location = 0) in vec2 position;\n"
                                            "layout (location = 1) in vec2 texCoord;\n"
                                            "out vec2 TexCoord;\n"
                                            "uniform vec2 hotspot;\n"
                                            "uniform mat4 transform;\n"
                                            "uniform mat4 size;\n"
                                            "void main()\n"
                                            "{\n"
                                                "gl_Position = transform * size  * vec4(position-hotspot, 0.0f, 1.0f);\n"
                                                "TexCoord = texCoord;\n"
                                            "}\0";
#else
        const GLchar* fragmentShaderSource = "#version 330 core\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D mainTexture;\n"
                                           "uniform vec4 colorFactor;\n"
                                           "void main()\n"
                                           "{\n"
                                                "color = texture(mainTexture, TexCoord) * colorFactor;\n"
                                           "}\0";

        const GLchar* vertexShaderSource =  "#version 330 core\n"
                                             "layout (location = 0) in vec2 position;\n"
                                             "layout (location = 1) in vec2 texCoord;\n"
                                             "out vec2 TexCoord;\n"
                                             "uniform vec2 hotspot;\n"
                                             "uniform mat4 transform;\n"
                                             "uniform mat4 size;\n"
                                             "void main()\n"
                                             "{\n"
                                                "gl_Position = transform * size * vec4(position-hotspot, 0.0f, 1.0f);\n"
                                                "TexCoord = texCoord;\n"
                                             "}\0";

#endif

        m_shaderProgram = loadShader(fragmentShaderSource, vertexShaderSource);

        

#ifdef GLES2
        const GLchar* fragmentShaderSource2 = "#version 300 es\n"
                                           "precision mediump float;\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D mainTexture;\n"
                                           "void main()\n"
                                           "{\n"
                                                "color = texture(mainTexture, TexCoord);\n"
                                           "}\0";

        const GLchar* vertexShaderSource2 =  "#version 300 es\n"
                                             "layout (location = 0) in vec2 position;\n"
                                             "layout (location = 1) in vec2 texCoord;\n"
                                             "out vec2 TexCoord;\n"
                                             "uniform mat4 transform;\n"
                                             "void main()\n"
                                             "{\n"
                                                "gl_Position = transform * vec4(position, 0.0f, 1.0f);\n"
                                                "TexCoord = texCoord;\n"
                                             "}\0";
#else
        const GLchar* fragmentShaderSource2 = "#version 330 core\n"
                                           "in vec2 TexCoord;\n"
                                           "out vec4 color;\n"
                                           "uniform sampler2D mainTexture;\n"
                                           "void main()\n"
                                           "{\n"
                                                "color = texture(mainTexture, TexCoord);\n"
                                           "}\0";

        const GLchar* vertexShaderSource2 =  "#version 330 core\n"
                                             "layout (location = 0) in vec2 position;\n"
                                             "layout (location = 1) in vec2 texCoord;\n"
                                             "out vec2 TexCoord;\n"
                                             "uniform mat4 transform;\n"
                                             "void main()\n"
                                             "{\n"
                                                "gl_Position = transform * vec4(position, 0.0f, 1.0f);\n"
                                                "TexCoord = texCoord;\n"
                                             "}\0";

#endif

        m_renderTextureShaderProgram = loadShader(fragmentShaderSource2, vertexShaderSource2);

 

        GLfloat vertices[] = {
                // Positions        // Texture Coords
                1.0f, 1.0f,         1.0f, 1.0f, // Bottom Right
                1.0f, 0.0f,         1.0f, 0.0f, // Top Right
                0.0f, 0.0f,         0.0f, 0.0f, // Top Left
                0.0f, 1.0f,         0.0f, 1.0f  // Bottom Left
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
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // TexCoord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO
    }

    void GLRenderer::screenChange(int w, int h) 
    {
        m_width = w;
        m_height = h;

        if(m_frameBuffer == 0)
        {
            glGenFramebuffers(1, &m_frameBuffer);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

        if(m_renderTexture == 0)
        {
            glGenTextures(1, &m_renderTexture);
        }
        glBindTexture(GL_TEXTURE_2D, m_renderTexture);

        auto virtualWidth = Context::getInstance().getGameConfig().width;
        auto virtualHeight = Context::getInstance().getGameConfig().height;

        if(virtualWidth / static_cast<float>(m_width) > virtualHeight / static_cast<float>(m_height))
        {
            m_proportionWidth = m_width;
            m_proportionHeight = (virtualHeight / static_cast<float>(virtualWidth)) * m_proportionWidth;
        }
        else
        {
            m_proportionHeight = m_height;
            m_proportionWidth = (virtualWidth / static_cast<float>(virtualHeight)) * m_proportionHeight;
        }

        m_wratio = m_proportionWidth/static_cast<float>(m_width);
        m_hratio = m_proportionHeight/static_cast<float>(m_height);

        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_proportionWidth, m_proportionHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTexture, 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Context::getInstance().log("Frame buffer wasn't created");
            return;
        }

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); 
    }

    void GLRenderer::draw(std::shared_ptr<IScene> scene)
    {
        glViewport(0, 0, static_cast<int>( m_proportionWidth ), static_cast<int>( m_proportionHeight) );

        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram( m_shaderProgram );

        auto layers = scene->getObjects();

        for(auto& layer: layers)
        {
            for(auto& object: layer)
            {
                // if(drawable->enabled())
                {
                    auto transform = object->getComponent<Transform>();

                    GLuint transformLoc = glGetUniformLocation(m_shaderProgram, "transform");        
                    
                    float aspectw = 1.0f;
                    float aspecth = 1.0f;

                    if(m_proportionWidth > m_proportionHeight)
                    {
                        aspecth = (m_proportionHeight/static_cast<float>(m_proportionWidth));
                    }
                    else if(m_proportionHeight > m_proportionWidth)
                    {
                        aspectw = (m_proportionWidth/static_cast<float>(m_proportionHeight));
                    }

                    Matrixf33 trans(1.0f);

                    trans = Matrixf33::cut(trans, 0.0f, aspectw, aspecth, 0.0f);
                    
                    if(transform)
                    {
                        trans = trans * transform->getMatrix();
                    }

                    glm::mat4 glmMat(1.0f);

                    glmMat[0][0] = trans[0][0];
                    glmMat[1][0] = trans[0][1];
                    glmMat[2][0] = 0.0f;
                    glmMat[3][0] = trans[0][2];

                    glmMat[0][1] = trans[1][0];
                    glmMat[1][1] = trans[1][1];
                    glmMat[2][1] = 0.0f;
                    glmMat[3][1] = trans[1][2];

                    glmMat[0][2] = 0.0f;
                    glmMat[1][2] = 0.0f;
                    glmMat[2][2] = 1.0f;
                    glmMat[3][2] = 0.0f;

                    glmMat[0][3] = trans[2][0];
                    glmMat[1][3] = trans[2][1];
                    glmMat[2][3] = 0.0f;
                    glmMat[3][3] = trans[2][2];

                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glmMat));

                    GLuint colorLocation = glGetUniformLocation(m_shaderProgram, "colorFactor");
                    glm::vec4 glmColor(1.0f, 1.0f, 1.0f, 1.0f);
                    if(transform)
                    {
                        auto color = transform->getColor();
                        glmColor = glm::vec4(color.r, color.g, color.b, color.a);
                    }
                    glUniform4fv(colorLocation, 1, glm::value_ptr(glmColor));

                    GLuint hotspotLocation = glGetUniformLocation(m_shaderProgram, "hotspot");

                    auto drawables = object->getDrawables();
                    float fwidth = static_cast<float>(m_width);
                    float fheight = static_cast<float>(m_height);
                    GLuint sizeLoc = glGetUniformLocation(m_shaderProgram, "size");

                    for(auto& drawable: drawables)
                    {
                        auto size = drawable->getSize();

                        auto virtualWidth = Context::getInstance().getGameConfig().width;
                        auto virtualHeight = Context::getInstance().getGameConfig().height;

                        auto minScreen = static_cast<float>(std::min(virtualWidth, virtualHeight));
                        auto maxScreen = static_cast<float>(std::max(virtualWidth, virtualHeight));

                        auto s = size;

                        s.x = size.x/virtualWidth;
                        s.y = size.y/virtualHeight;

                        if(virtualWidth > virtualHeight) 
                        {
                            s.y = s.y * (minScreen/maxScreen);
                        } else if(virtualWidth < virtualHeight)
                        {
                            s.x = s.x * (minScreen/maxScreen);
                        }

                        auto sizeTransform = glm::scale(glm::mat4(1.0f), glm::fvec3(s.x, s.y, 1.0f));
                        glUniformMatrix4fv(sizeLoc, 1, GL_FALSE, glm::value_ptr(sizeTransform));
                        auto hotspot = drawable->getHotspot();
                        glUniform2fv(hotspotLocation, 1, glm::value_ptr(glm::fvec2(hotspot.x/size.x, hotspot.y/size.y)));
                        drawable->draw();
                    }
                }
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram( m_renderTextureShaderProgram );

        GLuint transformLoc = glGetUniformLocation(m_renderTextureShaderProgram, "transform");        

        auto trans = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f);

        if(m_width > m_proportionWidth)
        {
            trans = glm::translate(trans, glm::vec3((m_width - m_proportionWidth) / static_cast<float>(m_width) / 2.0f, 0.0f, 0.0f));
        }

        if(m_height > m_proportionHeight)
        {
            trans = glm::translate(trans, glm::vec3(0.0f, (m_height - m_proportionHeight) / static_cast<float>(m_height) / 2.0f, 0.0f));
        }
        
        trans = glm::scale(trans, glm::vec3(m_wratio, m_hratio, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); 


        glBindVertexArray(VAO);

        glBindTexture(GL_TEXTURE_2D, m_renderTexture );

        glViewport(0,0,m_width,m_height);

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

    int GLRenderer::getHeight()
    {
        return m_height;
    }

    FCoord GLRenderer::getScaledScreenSize() const
    {
        return { m_proportionWidth, m_proportionHeight };
    }

    int GLRenderer::getBiggerSide() const
    {
        return m_width > m_height ? m_width : m_height;
    }

    int GLRenderer::getSmallerSide() const
    {
        return m_width < m_height ? m_width : m_height;
    }

    GLuint GLRenderer::loadShader(const GLchar* fragmentShaderSource, const GLchar* vertexShaderSource)
    {

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
            apc::Context::getInstance().log( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" );
            apc::Context::getInstance().log( infoLog );
            return 0;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);


        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            apc::Context::getInstance().log( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" );
            apc::Context::getInstance().log( infoLog );
            return 0;
        }

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            apc::Context::getInstance().log( "ERROR::SHADER::shaderProgram::LINKING_FAILED\n" );
            apc::Context::getInstance().log( infoLog );
            return 0;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return shaderProgram;
    }
}