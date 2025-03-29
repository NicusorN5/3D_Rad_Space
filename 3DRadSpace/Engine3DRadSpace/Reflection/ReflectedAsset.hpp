#pragma once
#include "ReflectedField.hpp"
#include "../Content/AssetID.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<Content::AssetType T>
	class ReflectedAsset: public ReflectedField<Content::AssetID<T>>
	{
	public:
		ReflectedAsset(const size_t offset_obj_field, const std::string& visibleName, const std::string& description) :
			ReflectedField(offset_obj_field, visibleName, description, Content::AssetID<T>())
		{
		}

		Reflection::UUID AssetUUID() const noexcept
		{
			return Internal::AssetUUIDReader::GetUUID<T>();
		}

		const char* FileExtension() const noexcept
		{
			return Internal::AssetUUIDReader::GetFileExtension<T>();
		}
	};
}