#include "ContentManager.hpp"
#include "ContentManager.h"
#include "../Logging/Logging.hpp"
#include "../Graphics/IGraphicsDevice.hpp"
#include "Assets/Assets.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

ContentManager::AssetFactory::AssetFactory(IGame* owner) :
	_owner(owner)
{
	_services[typeid(void)] = nullptr;
}

IAsset* ContentManager::AssetFactory::Create(const Reflection::UUID& uuid, const std::filesystem::path& path)
{
	for (const auto& [r_uuid, ctor, service] : _types)
	{
		if (r_uuid == uuid)
		{
			return ctor(service, path);
		}
	}
	return nullptr;
}

ContentManager::ContentManager(IGame* owner) :
	_lastID(1),
	_factory(owner),
	_owner(owner)
{
	//We add a null asset at index 0 because reference IDs are unsigned integers.
	_assets.emplace_back(nullptr);
}

IAsset* ContentManager::Load(const Reflection::UUID &uuid, const std::filesystem::path& path, unsigned* refID)
{
	auto asset = _factory.Create(uuid, path);
	
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
	auto uuid = _assets[id].Entry->GetUUID();
	auto path = _assets[id].Path;

	Logging::SetLastMessage(std::format("Loaded asset ID {} path {} UUID {}", id, path.string(), uuid));
	auto asset = _factory.Create(uuid, path);
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

void ContentManager::Clear()
{
	_assets.clear();
	_assets.emplace_back(nullptr);
}

size_t ContentManager::Count() const noexcept
{
	return _assets.size();
}

IGraphicsDevice* ContentManager::GetDevice() const noexcept
{
	return _owner->GetService<IGraphicsDevice>({});
}

E3DRSP_IAsset E3DRSP_ContentManager_Load(E3DRSP_ContentManager content, const E3DRSP_UUID* uuid, const char* path, unsigned* id)
{
	if (content == nullptr) return nullptr;

	return static_cast<ContentManager*>(content)->Load(
		*reinterpret_cast<const Reflection::UUID*>(uuid),
		std::filesystem::path(path),
		id
	);
}

void E3DRSP_ContentManager_Reload(E3DRSP_ContentManager content, unsigned id)
{
	if (content == nullptr) return;
	static_cast<ContentManager*>(content)->Reload(id);
}

void E3DRSP_ContentManager_Remove(E3DRSP_ContentManager content, unsigned id)
{
	if (content == nullptr) return;
	static_cast<ContentManager*>(content)->RemoveAsset(id);
}

void E3DRSP_ContentManager_Clear(E3DRSP_ContentManager content)
{
	if (content == nullptr) return;
	static_cast<ContentManager*>(content)->Clear();
}

size_t E3DRSP_ContentManager_Count(E3DRSP_ContentManager content)
{
	if (content == nullptr) return 0;
	return static_cast<ContentManager*>(content)->Count();
}