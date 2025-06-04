#pragma once
/*
#include "ReflectedField.hpp"
#include "../Content/AssetID.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<Content::AssetType T>
	class ReflectedAsset: public ReflectedField<Content::AssetID<T>>
	{
		Reflection::UUID _uuid;
		const char* _extensions;

	public:
		ReflectedAsset(const size_t offset_obj_field, const std::string& visibleName, const std::string& description) :
			ReflectedField(offset_obj_field, visibleName, description, Content::AssetID<T>()),
			_uuid(Internal::AssetUUIDReader::GetUUID<T>()),
			_extensions(Internal::AssetUUIDReader::GetFileExtension<T>())
		{
		}

		Reflection::UUID AssetUUID() const noexcept
		{
			return _uuid;
		}

		const char* FileExtension() const noexcept
		{
			return _extensions;
		}
	};
}
*/