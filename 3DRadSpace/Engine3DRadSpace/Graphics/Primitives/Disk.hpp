#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Represents a disk formed by an triangle list.
	/// </summary>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT Disk : public IPrimitive
	{
	public:
		Disk(IGraphicsDevice* device, float radius, unsigned resolution, const Math::Color& color);

		[[nodiscard]] static std::vector<VertexPositionColor> CreateDiskVertices(float radius, unsigned resolution, const Math::Color& color);
		[[nodiscard]] static std::vector<unsigned> CreateDiskIndices(unsigned resolution);

		~Disk() override = default;
	};
}