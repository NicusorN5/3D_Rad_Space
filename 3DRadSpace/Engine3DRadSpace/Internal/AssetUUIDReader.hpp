#pragma once
#include "../Reflection/UUID.hpp"
#include "../Content/IAsset.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace::Internal
{
	/// <summary>
	/// Since it is impossible to obtain a vtable function without a instance, this exists.
	/// </summary>
	struct AssetUUIDReader
	{
	public:
		template<Content::AssetType T>
		static Reflection::UUID GetUUID(Tag<T> dummy)
		{
			T useless_instance(AssetUUIDReader{});
			return useless_instance.GetUUID();
		}
	};
}