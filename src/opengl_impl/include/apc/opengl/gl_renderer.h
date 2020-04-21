#pragma once
#include "apc/renderer.h"

#include "apc/resource_manager.h"
#include "apc/opengl/resources/gl_texture.h"
#include "apc/scene.h"

#include <list>
#include <memory>

namespace apc
{
    class GLRenderer : public IRenderer
    {
    public:
        GLRenderer();
        void init() override;
        void screenChange(int w, int h) override;
        void draw(std::shared_ptr<IScene> scene) override;
        void destroy() override;
        int getWidth() override;
        int getHeight() override;
        FCoord getScaledScreenSize() const override;
    private:
        static GLuint loadShader(const GLchar* fragmentShaderSource, const GLchar* vertexShaderSource);

        int getBiggerSide() const;
        int getSmallerSide() const;
        float m_hratio;
        float m_wratio;
        // GLTextureResourcePtr m_texture;
        // GLuint VBO, VAO, EBO;
        GLuint m_shaderProgram;
        GLuint m_renderTextureShaderProgram;
        int m_width;
        int m_height;
        GLuint m_frameBuffer;
        GLuint m_renderTexture;

        GLuint VBO, VAO, EBO;

        float m_proportionWidth;
        float m_proportionHeight;
    };
}