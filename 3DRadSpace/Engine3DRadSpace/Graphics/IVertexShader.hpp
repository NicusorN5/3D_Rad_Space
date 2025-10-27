#pragma once
#include "IShader.hpp"
#include "InputLayoutElement.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IVertexShader : public IShader
	{
	public:
		virtual std::span<InputLayoutElement> InputLayout() = 0;

		~IVertexShader() override = default;
	};
}