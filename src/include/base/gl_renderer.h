#pragma once
#include "core/renderer.h"

#include "core/resource_manager.h"
#include "base/resources/gl_texture.h"
#include "core/scene.h"

#include <list>
#include <memory>

namespace APC
{
    class GLRenderer : public IRenderer
    {
    public:
        GLRenderer();
        void init(int w, int h) override;
        void draw(std::shared_ptr<IScene> scene) override;
        void destroy() override;
        int getWidth() override;
        int getHeight() override;
    private:
        // GLTextureResourcePtr m_texture;
        // GLuint VBO, VAO, EBO;
        GLuint shaderProgram;
        int m_width, m_height;
    };
}