#pragma once

namespace Engine3DRadSpace
{
	/// <summary>
	/// Type carrier.
	/// </summary>
	/// <typeparam name="T">Template type.</typeparam>
	template<typename T> struct Tag
	{
		using Type = T;
	};
}