#include "Assets.hpp"
#include "FontAsset.hpp"
#include "ModelAsset.hpp"
#include "SkyboxAsset.hpp"
#include "TextureAsset.hpp"
#include "../Audio/Sound.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;

void Engine3DRadSpace::Internal::RegisterDefaultTypes(ContentManager* manager)
{
	manager->RegisterType<FontAsset>({});
	manager->RegisterType<ModelAsset>({});
	manager->RegisterType<SkyboxAsset>({});
	manager->RegisterType<TextureAsset>({});
	manager->RegisterType<Audio::Sound>({});
}