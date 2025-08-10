#include "Assets.hpp"

#include "../Graphics/Font.hpp"
#include "../Content/Assets/NullAsset.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Content/Assets/SkyboxAsset.hpp"
#include "..\Content\AssetFactory.hpp"
#include "../Audio/Sound.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Internal;

void Engine3DRadSpace::Internal::RegisterDefaultAssets()
{
	if (asset_types.empty())
	{
		RegisterAssetType<Assets::NullAsset>();
		RegisterAssetType<Graphics::Texture2D>();
		RegisterAssetType<Graphics::Model3D>();
		RegisterAssetType<Graphics::Font>();
		RegisterAssetType<Audio::Sound>();
		RegisterAssetType<Assets::SkyboxAsset>();
	}
}