#include "Box.hpp"
#include "../IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

std::array<VertexPositionColor, 8> Box::CreateVertices(const BoundingBox&b, const Color& color)
{
    return std::array<VertexPositionColor, 8>
    {
        VertexPositionColor{ b.Position, color }, // 0
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, 0, 0), color }, // 1
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y, 0), color }, // 2
        VertexPositionColor{ b.Position + Vector3(0, 0, b.Scale.Z), color }, // 3
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, b.Scale.Y, 0), color }, // 4
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y, b.Scale.Z), color }, // 5
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, 0, b.Scale.Z), color }, // 6
        VertexPositionColor{ b.Position + b.Scale, color }, // 7
    };
}

std::array<unsigned, 36> Box::CreateIndices()
{
    return
    {
        //-Y face
        0, 3, 6,
        0, 6, 1,
        //+Y face
        7, 5, 2,
        4, 7, 2,
        // -X face
        0, 2, 5,
        0, 5, 3,
        //+X face
        7, 4, 1,
        6, 7, 1,
        //-Z face
        1, 4, 2,
        1, 2, 0,
        //+Z face
        3, 5, 7,
        3, 7, 6
    };
}

Box::Box(IGraphicsDevice *device, const BoundingBox&b, Color color) :
    IPrimitive(device),
    _box(b)
{
    auto box_vertices = CreateVertices(b, color);
    _vertices = device->CreateVertexBuffer<VertexPositionColor>(box_vertices, BufferUsage::ReadOnlyGPU);
   
    std::array<unsigned, 36> indices = CreateIndices();
    _indices = device->CreateIndexBuffer(indices);
}

BoundingBox Box::GetBoundingBox() const noexcept
{
    return _box;
}

void Box::SetBoundingBox(const BoundingBox&b)
{
    _box = b;

    auto box_vertices = CreateVertices(b, _color);
    _vertices->SetData<VertexPositionColor>(box_vertices);
}

Color Box::GetColor() const noexcept
{
    return _color;
}

void Box::SetColor(const Color&color)
{
    _color = color;

    auto verts = CreateVertices(_box, color);
    _vertices->SetData<VertexPositionColor>(verts);
}

IVertexBuffer* Box::GetVertexBuffer() const noexcept
{
    return _vertices.get();
}

IIndexBuffer* Box::GetIndexBuffer() const noexcept
{
    return _indices.get();
}