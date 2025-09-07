#include "Assets.hpp"

#include "../Graphics/Font.hpp"
#include "Assets/TextureAsset.hpp"
#include "Assets/FontAsset.hpp"
#include "Assets/NullAsset.hpp"
#include "../Graphics/Model3D.hpp"
#include "Assets/SkyboxAsset.hpp"
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
		RegisterAssetType<Assets::TextureAsset>();
		RegisterAssetType<Assets::ModelAsset>();
		RegisterAssetType<Assets::FontAsset>();
		RegisterAssetType<Audio::Sound>();
		RegisterAssetType<Assets::SkyboxAsset>();
	}
}