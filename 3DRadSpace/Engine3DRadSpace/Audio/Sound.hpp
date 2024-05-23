#pragma once
#include "../Content/IAsset.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound : public Content::IAsset
	{
	public:
		Sound(const std::filesystem::path& path);

		Sound(const Sound&) = delete;
	};
}