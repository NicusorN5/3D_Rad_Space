#pragma once
#include "../../Core/Libs.hpp"

/// <summary>
/// C Equivalent of std::span.
/// </summary>
struct E3DRSP_RawSpan
{
	/// <summary>
	/// Pointer to the first element.
	/// </summary>
	void* Ptr;
	/// <summary>
	/// Number of elements.
	/// </summary>
	size_t Size;
};