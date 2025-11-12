#pragma once
#include "../Reflection/UUID.hpp"
#include "../Content/IAsset.hpp"
#include "Tag.hpp"

namespace Engine3DRadSpace::Internal
{
	/// <summary>
	/// HACK - Since it is impossible to obtain a vtable function without a instance, this exists. 
	/// DO NOT use constructors using this argument, as they create invalid objects!
	/// </summary>
	struct AssetUUIDReader
	{
		template<Content::AssetType T>
		static Reflection::UUID GetUUID(Tag<T> dummy)
		{
			(void)dummy;
			return (T(AssetUUIDReader{})).GetUUID();
		}

		template<Content::AssetType T>
		static const char* GetFileExtension(Tag<T> dummy)
		{
			(void)dummy;
			return (T(AssetUUIDReader{})).FileExtension();
		}

		template<Content::AssetType T>
		static std::type_index GetInitializationService(Tag<T> dummy)
		{
			(void)dummy;
			return (T(AssetUUIDReader{})).InitializationService();
		}
	};
}