#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Math
{
	template<typename T> 
	constexpr T ToRadians(T degrees)
	{
		return static_cast<T>(std::numbers::pi * degrees / 180);
	}

	template<typename T>
	constexpr T ToDegrees(T radians)
	{
		return static_cast<T>(radians * 180 / std::numbers::pi);
	}

	constexpr double E3DRSP_MATH_EXPORT CatmullRom(double value1, double value2, double value3, double value4, double amount);
	constexpr double E3DRSP_MATH_EXPORT Hermite(double value1, double tangent1, double value2, double tangent2, double amount);

	//Axis aglined check for one single axis.
	constexpr bool E3DRSP_MATH_EXPORT AABB(float p1, float w1, float p2, float w2);
	constexpr bool E3DRSP_MATH_EXPORT AABB(double p1, double w1, double p2, double w2);

	constexpr double E3DRSP_MATH_EXPORT SmoothStep(double value1, double value2, double amount);
	constexpr double E3DRSP_MATH_EXPORT ReLU(double x);

	constexpr bool E3DRSP_MATH_EXPORT WithinEpsilon(float a, float b);
}