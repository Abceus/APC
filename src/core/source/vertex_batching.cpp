#include "vertex_batching.h"

#include <algorithm>

namespace apc
{
    VertexBatcher::VertexBatcher()
        : m_viewMatrix( Matrixf33(1.0f) )
    {

    }

    void VertexBatcher::initLayers(const std::vector<std::string>& layers)
    {
        m_layers = layers;
        m_batches.resize(m_layers.size());
    }

    void VertexBatcher::setVirtualScreenSize( const FCoord& size )
    {
        m_virtualScreenSize = size;

        float aspectw = 1.0f;
        float aspecth = 1.0f;

        if(m_virtualScreenSize.x > m_virtualScreenSize.y)
        {
            aspecth = (m_virtualScreenSize.y/static_cast<float>(m_virtualScreenSize.x));
        }
        else if(m_virtualScreenSize.y > m_virtualScreenSize.x)
        {
            aspectw = (m_virtualScreenSize.x/static_cast<float>(m_virtualScreenSize.y));
        }

        m_viewMatrix = Matrixf33::cut( Matrixf33(1.0f), 0.0f, aspectw, aspecth, 0.0f );
    }

    void VertexBatcher::addVertices( const std::string& layer, const TexturePtr texture, const std::vector<FCoord>& vertices, 
                        const std::vector<FCoord>& textureCoords, const std::vector<unsigned short>& indices, 
                        const Matrixf33& matrix, const Color& color )
    {
        if( vertices.size() != textureCoords.size())
        {
            return;
        }
        
        auto foundLayer = std::find( m_layers.begin(), m_layers.end(), layer );
        if( foundLayer == m_layers.end() )
        {
            return;
        }

        auto layerIndex = std::distance(m_layers.begin(), foundLayer);
        auto& layerVector = m_batches[layerIndex];
        auto foundBatch = std::find_if( layerVector.begin(), layerVector.end(), 
                                            [this, &texture](const Batch& batch) -> bool { return batch.texture == texture; });

        if(foundBatch == layerVector.end())
        {
            Batch batch; 
            batch.texture = texture;
            for(size_t i = 0; i < vertices.size(); i++)
            {
                batch.vertices.emplace_back(Vertex{ FCoord::getTransformed( vertices[i], m_viewMatrix * matrix ), textureCoords[i], color });
            }
            batch.indices = indices;
            // batch.objectsCount = batch.indices.size() % 3;
            layerVector.emplace_back(batch);
        }
        else
        {
            auto& batch = *foundBatch;
            auto indexOffset = batch.vertices.size();

            for(size_t i = 0; i < vertices.size(); i++)
            {
                batch.vertices.emplace_back(Vertex{ FCoord::getTransformed( vertices[i], m_viewMatrix * matrix ), textureCoords[i], color });
            }

            auto newIndices = indices;
            for(auto& index: indices)
            {
                std::for_each(newIndices.begin(), newIndices.end(), [indexOffset](unsigned short &n){ n += indexOffset; });
            }

            std::merge(batch.indices.begin(), batch.indices.end(), newIndices.begin(), newIndices.end(), std::back_inserter(batch.indices));

            // batch.objectsCount = batch.indices.size() % 3;
        }
    }
        
    std::vector<std::vector<Batch>> VertexBatcher::getBatches() const
    {
        return m_batches;
    }
}