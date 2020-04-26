#pragma once

#include <string>

#include "apc/coord.h"
#include "apc/color.h"
#include "apc/matrix.h"
#include "apc/texture.h"

namespace apc
{
    struct Vertex 
    {
        FCoord coord;
        FCoord textureCoord;
        Color color;
    };

    struct Batch
    {
        TexturePtr texture;
        std::vector<Vertex> vertices;
        std::vector<unsigned short> indices;
        // size_t objectsCount = 0;
    };

    class VertexBatcher
    {
    public:
        VertexBatcher();

        void initLayers(const std::vector<std::string>& layers);

        void setVirtualScreenSize( const FCoord& size );

        void addVertices( const std::string& layer, const TexturePtr texture, const std::vector<FCoord>& vertices, 
                            const std::vector<FCoord>& textureCoords, const std::vector<unsigned short>& indices, 
                            const Matrixf33& matrix, const Color& color );
        
        std::vector<std::vector<Batch>> getBatches() const;

    private:
        std::vector<std::string> m_layers;
        std::vector<std::vector<Batch>> m_batches;
        Matrixf33 m_viewMatrix;
        FCoord m_virtualScreenSize;
    };
}