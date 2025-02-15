/// ------------------------------------------------------------------------------------------------
/// File:   Algorithms/LevenshteinDistance.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Algorithms
{
	/// <summary>
	/// A implementation of Damerau Levenshtein string edit distance. 
	/// </summary>
	/// <param name="a">A string</param>
	/// <param name="b">A string</param>
	/// <returns>String distance</returns>
	/// <remarks>
	/// Time complexity is O(N*M).
	/// A temporary N*M matrix is dynamically allocated while calculating the distance.
	/// </remarks>
	int DLLEXPORT DamerauLevenshteinDistance(const std::string& a, const std::string& b);
}