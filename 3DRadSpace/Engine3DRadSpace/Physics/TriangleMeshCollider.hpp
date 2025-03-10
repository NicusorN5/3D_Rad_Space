#pragma once
#include "ICollider.hpp"
#include "../Graphics/VertexDeclarations.hpp"

namespace Engine3DRadSpace::Physics
{
	class TriangleMeshCollider : ICollider
	{
	public:
		TriangleMeshCollider(
			PhysicsEngine* physics,
			std::span<Graphics::VertexPosition> pos,
			std::span<unsigned int> vertices
		);
	};
}