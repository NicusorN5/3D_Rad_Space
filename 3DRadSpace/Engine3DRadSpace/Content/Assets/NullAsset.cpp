#include "NullAsset.hpp"
#include "../../Internal/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;

NullAsset::NullAsset(IService* service, const std::filesystem::path& dummy)
{
	(void)service;
	(void)dummy;
}

NullAsset::NullAsset(Internal::AssetUUIDReader dummy)
{
	(void)dummy;
}

Reflection::UUID NullAsset::GetUUID() const noexcept
{
	return Reflection::UUID();
}

const char* Engine3DRadSpace::Content::Assets::NullAsset::FileExtension() const noexcept
{
	return "All Files(*.*)\0*.*\0\0";
}

std::type_index NullAsset::InitializationService() const noexcept
{
	return typeid(void);
}