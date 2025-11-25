#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	template<typename T>
	class IAssetWrapper : public IAsset
	{
	protected:
		std::optional<T> _asset;

		IAssetWrapper(T&& asset) noexcept : _asset(std::move(asset)) 
		{
		}

		IAssetWrapper() noexcept
		{
		}

	public:
		operator T& ()
		{
			return *_asset;
		}

		const T* Get() const
		{
			return _asset.operator->();
		}

		T* Get()
		{
			return _asset.operator->();
		}

		const T* operator->() const
		{
			return _asset.operator->();
		}

		T* operator->()
		{
			return _asset.operator->();
		}

		bool HasValue() const noexcept
		{
			return _asset.has_value();
		}

	public:
		~IAssetWrapper() override = default;
	};
}