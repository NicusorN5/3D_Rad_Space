#include "ContentManager.hpp"
#include "../Core/Logging.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

ContentManager::ContentManager(Game* owner) :
	_lastID(1),
	_factory(owner)
{
	//We add a null asset at index 0 because reference IDs are unsigned integers.
	_assets.emplace_back(nullptr);
}

IAsset* ContentManager::Load(const Reflection::UUID &uuid, const std::filesystem::path& path, unsigned* refID)
{
	auto asset = _factory.CreateAssetInstance(uuid, path);
	
	std::unique_ptr<IAsset> ptrAsset;
	ptrAsset.reset(asset);

	_assets.emplace_back(std::move(ptrAsset), path);
	_assets[_assets.size() - 1].ID = _assets.size() - 1;

	if (refID)
	{
		*refID = static_cast<unsigned>(_assets.size() - 1);
	}

	return asset;
}

void ContentManager::Reload(unsigned id)
{
	auto asset = _factory.CreateAssetInstance(_assets[id].Entry->GetUUID(), _assets[id].Path);
	_assets[id].Entry.reset(asset);
}

std::filesystem::path ContentManager::GetAssetPath(unsigned id) const noexcept
{
	return _assets[id].Path;
}

Reflection::UUID ContentManager::GetAssetType(unsigned id) const noexcept
{
	return _assets[id].Type;
}

std::string ContentManager::GetAssetName(unsigned id) const noexcept
{
	return _assets[id].Name;
}

std::vector<ContentManager::AssetEntry>::iterator ContentManager::begin()
{
	return std::next(_assets.begin());
}

std::vector<ContentManager::AssetEntry>::iterator ContentManager::end()
{
	return _assets.end();
}

void ContentManager::RemoveAsset(unsigned id)
{
	_assets.erase(_assets.begin() + id);
}

void Engine3DRadSpace::Content::ContentManager::Clear()
{
	_assets.clear();
	_assets.emplace_back(nullptr);
}

size_t Engine3DRadSpace::Content::ContentManager::Count() const noexcept
{
	return _assets.size();
}

GraphicsDevice* ContentManager::GetDevice() const noexcept
{
	return _factory.Device();
}