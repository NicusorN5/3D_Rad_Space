#include "Assets.hpp"

#include "../Content/Assets/Font.hpp"
#include "../Content/Assets/NullAsset.hpp"
#include "../Content/Assets/Model3D.hpp"
#include "../Content/Assets/SkyboxAsset.hpp"
#include "..\Content\AssetFactory.hpp"
#include "../Audio/Sound.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Internal;

void Engine3DRadSpace::Internal::RegisterDefaultAssets()
{
	if (asset_types.empty())
	{
		RegisterAssetType<Assets::NullAsset>();
		RegisterAssetType<Graphics::Texture2D>();
		RegisterAssetType<Assets::Model3D>();
		RegisterAssetType<Assets::Font>();
		RegisterAssetType<Audio::Sound>();
		RegisterAssetType<Assets::SkyboxAsset>();
	}
}