#pragma once
#include "../Math/Point.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;

	class E3DRSP_GRAPHICS_EXPORT IGraphicsDevice
	{
	protected:
		IGraphicsDevice() = default;
	public:
		virtual ITexture2D* CreateTexture(const std::filesystem::path& path);

		virtual ~IGraphicsDevice() = default;
	};
}