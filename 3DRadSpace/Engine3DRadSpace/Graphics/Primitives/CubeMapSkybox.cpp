#include "CubeMapSkybox.hpp"
#include "Box.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

CubeMapSkybox::CubeMapSkybox(GraphicsDevice* device, std::array<Texture2D, 6> &&faces) :
	IPrimitive(device), 
	_faces(std::move(faces))
{
	//std::array<VertexPositionUV, 8> vertices = 
 //   {
 //       VertexPositionUV{ b.Position, color }, // 0
 //       VertexPositionUV{ b.Position + Vector3(b.Scale.X, 0, 0), color }, // 1
 //       VertexPositionUV{ b.Position + Vector3(0, b.Scale.Y, 0), color }, // 2
 //       VertexPositionUV{ b.Position + Vector3(0, 0, b.Scale.Z), color }, // 3
 //       VertexPositionUV{ b.Position + Vector3(b.Scale.X, b.Scale.Y, 0), color }, // 4
 //       VertexPositionUV{ b.Position + Vector3(0, b.Scale.Y, b.Scale.Z), color }, // 5
 //       VertexPositionUV{ b.Position + Vector3(b.Scale.X, 0, b.Scale.Z), color }, // 6
 //       VertexPositionUV{ b.Position + b.Scale, color }, // 7
 //   };

	//_vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, vertices);

	std::array<unsigned, 36> indices = Box::CreateIndices();
	_indices = std::make_unique<IndexBuffer>(device, indices);
}
