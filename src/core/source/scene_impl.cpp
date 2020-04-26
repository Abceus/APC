#include "scene_impl.h"
#include <algorithm>
#include "context.h"

namespace apc
{
    void Scene::initLayers(const std::vector<std::string>& layers)
    {
        m_layers = layers;
        m_objects.clear();
        // m_objects.resize(m_layers.size());
        // m_rootNode = std::make_shared<Position>();
    }

    std::vector<std::string> Scene::getLayers() const
    {
        return m_layers;
    }

    // void Scene::draw(GLuint shaderProgram)
    // {
    //     for(auto& layerDrawables: m_drawables)
    //     {
    //         for(auto& drawable: layerDrawables)
    //         {
    //             if(drawable->enabled())
    //             {
    //                 GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    //                 const float aspect = Context::getInstance().getScreenSize().x/static_cast<float>(Context::getInstance().getScreenSize().y);
    //                 auto trans = glm::ortho(0.0f, aspect, 1.0f, 0.0f, -1.0f, 1.0f);
    //                 glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans * drawable->getRenderNode()->getMatrix()));

    //                 GLuint colorLocation = glGetUniformLocation(shaderProgram, "colorFactor");
    //                 auto color = drawable->getRenderNode()->getColor();
    //                 glm::vec4 glmColor(color.r, color.g, color.b, color.a);
    //                 glUniform4fv(colorLocation, 1, glm::value_ptr(glmColor));
    //                 drawable->draw();
    //             }
    //         }
    //     }
    // }

    // std::shared_ptr<RenderNode> Scene::getRootNode() const 
    // {
    //     return m_rootNode;
    // }

    // void Scene::addDrawable(std::shared_ptr<IDrawable> drawable, std::string layer)
    // {
    //     auto layerIt = std::find( m_layers.begin(), m_layers.end(), layer);
    //     if(layerIt != m_layers.end())
    //     {
    //         auto index = std::distance(m_layers.begin(), layerIt);
    //         m_drawables[index].emplace_back(drawable);
    //     }
    // }

    // void Scene::removeDrawable(std::shared_ptr<IDrawable> drawable, std::string layer)
    // {
    //     auto layerIt = std::find( m_layers.begin(), m_layers.end(), layer);
    //     if(layerIt != m_layers.end())
    //     {
    //         auto index = std::distance(m_layers.begin(), layerIt);
    //         m_drawables[index].remove(drawable);
    //     }
    // }

    void Scene::addSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer)
    {
        // auto layerIt = std::find(m_layers.begin(), m_layers.end(), layer);
        // if(layerIt != m_layers.end())
        // {
        //     auto index = std::distance(m_layers.begin(), layerIt);
        //     m_objects[index].emplace_back(gameObject);
        // }
        auto objectIt = std::find(m_objects.begin(), m_objects.end(), gameObject);
        if(objectIt == m_objects.end())
        {
            m_objects.emplace_back(gameObject);
        }
    }

    void Scene::removeSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer)
    {
        // auto layerIt = std::find(m_layers.begin(), m_layers.end(), layer);
        // if(layerIt != m_layers.end())
        // {
        //     auto index = std::distance(m_layers.begin(), layerIt);
        //     m_objects[index].remove(gameObject);
        // }

        auto objectIt = std::find(m_objects.begin(), m_objects.end(), gameObject);
        if(objectIt != m_objects.end())
        {
            m_objects.erase(objectIt);
        }
    }

    // std::vector<std::list<std::shared_ptr<SceneObject>>> Scene::getObjects() const
    // {
    //     return m_objects;
    // }

    std::list<std::shared_ptr<SceneObject>> Scene::getObjects() const
    {
        return m_objects;
    }

    void Scene::update(float dt)
    {
        for(auto& object: m_objects)
        {
            // for(auto& drawable: layerDrawables)
            {
                // if(drawable->enabled())
                {
                    object->update(dt);
                }
            }
        }
    }

    void Scene::click(const ICoord& coord)
    {
        for(auto& object: m_objects)
        {
            // for(auto& drawable: layerDrawables)
            {
                // if(drawable->enabled())
                {
                    object->click(coord);
                }
            }
        }
    }
}