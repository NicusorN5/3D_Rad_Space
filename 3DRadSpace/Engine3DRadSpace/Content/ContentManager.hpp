#pragma once
#include "AssetID.hpp"
#include "../Core/IGame.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// 
	/// </summary>
	class E3DRSP_CONTENT_EXPORT ContentManager : public IService
	{
		struct AssetEntry
		{
			template<AssetType T>
			AssetEntry(IService* service, const std::filesystem::path& path) :
				Path(path),
				Entry(std::unique_ptr<T>(static_cast<IAsset*>(new T(service, path)))),
				Type(Entry->GetUUID()),
				RTTI(typeid(T)),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			template<AssetType T>
			AssetEntry(std::unique_ptr<T>&& asset, const std::filesystem::path& path) :
				Entry(std::move(asset)),
				Path(path),
				Type(Entry->GetUUID()),
				RTTI(typeid(T)),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			AssetEntry(std::unique_ptr<IAsset>&& asset, const std::filesystem::path& path) :
				Entry(std::move(asset)),
				Path(path),
				Type(Entry->GetUUID()),
				RTTI(typeid(Entry.get())),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			explicit AssetEntry(std::nullptr_t a) : Type(), RTTI(typeid(void)) {};

			AssetEntry(AssetEntry&&) noexcept = default;
			AssetEntry& operator=(AssetEntry&&) noexcept = default;

			std::unique_ptr<Content::IAsset> Entry;
			std::filesystem::path Path;
			Reflection::UUID Type;
			std::type_index RTTI;
			size_t ID = 0;
			std::string Name;
		};

		class AssetFactory
		{
			struct TypeEntry
			{
				Reflection::UUID UUID;
				std::function<IAsset* (IService*, const std::filesystem::path&)> Ctor;
				IService* Service;
			};

			std::vector<TypeEntry> _types;
			std::unordered_map<std::type_index, IService*> _services;

			IGame* _owner; 
		public:
			AssetFactory(IGame* owner);

			template<AssetType T>
			std::unique_ptr<T> Create(const std::filesystem::path& path)
			{
				RegisterType<T>({});

				return std::make_unique<T>(_services[typeid(T)], path);
			}

			template<AssetType T>
			bool RegisterType(Tag<T> dummy)
			{
				if (std::find_if(_types.begin(), _types.end(), [](const TypeEntry& t) -> bool
					{
						auto uuid = Internal::AssetUUIDReader::GetUUID<T>({});
						return uuid == t.UUID;
					}
				) != _types.end())
				{
					return false;
				}
				else
				{
					auto serviceType = Internal::AssetUUIDReader::GetInitializationService<T>({});

					_services[serviceType] = static_cast<IService*>(_owner->GetService(serviceType));

					_types.emplace_back(
						Internal::AssetUUIDReader::GetUUID<T>({}),
						[](IService* service, const std::filesystem::path& path) -> IAsset*
						{
							return static_cast<IAsset*>(new T(service, path));
						},
						_services[serviceType]
					);

					return true;
				}

			}

			IAsset* Create(const Reflection::UUID& uuid, const std::filesystem::path& path);

		} _factory;

		unsigned _lastID;
		std::vector<AssetEntry> _assets;
		IGame* _owner;
	public:
		ContentManager(IGame* owner);

		ContentManager(const ContentManager &) = delete;
		ContentManager(ContentManager &&) noexcept = default;

		ContentManager &operator =(const ContentManager &) = delete;
		ContentManager &operator =(ContentManager &&) noexcept = default;

		template<AssetType T>
		void RegisterType(Tag<T> dummy);

		template<AssetType T>
		T* Load(const std::filesystem::path& path, AssetID<T>* refID = nullptr);

		template<AssetType T, typename ...Args>
		T* Load(const std::filesystem::path& path, AssetID<T>* refID, Args&& ...params);

		IAsset* Load(const Reflection::UUID &uuid, const std::filesystem::path& path, unsigned* refID = nullptr);

		void Reload(unsigned ref);

		template<AssetType T>
		void Reload(unsigned id);

		template<AssetType T>
		void RemoveAsset(const T *asset);

		template<AssetType T>
		T *operator[](AssetID<T> ref);

		std::filesystem::path GetAssetPath(unsigned id) const noexcept;
		Reflection::UUID GetAssetType(unsigned id) const noexcept;
		std::string GetAssetName(unsigned id) const noexcept;

		std::vector<AssetEntry>::iterator begin();
		std::vector<AssetEntry>::iterator end();

		void RemoveAsset(unsigned id);
		void Clear();

		Graphics::IGraphicsDevice* GetDevice() const noexcept;
		size_t Count() const noexcept;

		~ContentManager() override = default;
	};










	///
	///										IMPLEMENTATION FOR ContentManager TEMPLATE METHODS
	/// ___________________________________________________________________________________________________________________________________________
	/// 
	///


	template<AssetType T>
	inline T* ContentManager::Load(const std::filesystem::path& path, AssetID<T> *refID)
	{
		auto asset = _factory.Create<T>(path);
		auto ptr = asset.get();

		_assets.emplace_back(std::move(asset), path);
		_assets[_assets.size() - 1].ID = _assets.size() - 1;

		if (refID)
		{
			*refID = static_cast<unsigned>(_assets.size() - 1);
		}
		return ptr;
	}

	template<AssetType T, typename ...Args>
	inline T* ContentManager::Load(const std::filesystem::path& path, AssetID<T>* refID, Args && ...params)
	{
		auto asset = _factory.Create<T>(path, std::forward<Args>(params)...);
		auto ptr = asset.get();

		_assets.emplace_back(std::move(asset), path);
		_assets[_assets.size() - 1].ID = _assets.size() - 1;

		if (refID)
		{
			*refID = _assets.size() - 1;
		}
		return ptr;
	}

	template<AssetType T>
	void ContentManager::RemoveAsset(const T* asset)
	{
		std::erase_if(_assets, [](std::unique_ptr<AssetEntry>& asset) -> bool
		{
			return (static_cast<T>(asset->Entry.get()) == asset);
		});
	}

	template<AssetType T>
	inline T* ContentManager::operator[](AssetID<T> ref)
	{
		return dynamic_cast<T*>(_assets[ref].Entry.get());
	}

	template<AssetType T>
	inline void ContentManager::RegisterType(Tag<T> dummy)
	{
		_factory.RegisterType<T>({});
	}
}