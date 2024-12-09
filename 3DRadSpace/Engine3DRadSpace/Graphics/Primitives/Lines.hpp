#pragma once
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Lines : public IPrimitive
	{
		std::unique_ptr<RasterizerState> _lineRasterizer;
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;
#endif
	public:
		Lines(GraphicsDevice *device, std::span<VertexPositionColor> points);

		Lines(const Lines &) = delete;
		Lines(Lines &&) noexcept = default;

		Lines &operator=(const Lines &) = delete;
		Lines &operator=(Lines &&) noexcept = default;

		VertexBufferV<VertexPositionColor>* GetVertexBuffer() const noexcept;
		RasterizerState* GetLineRasterizer() const noexcept;

		virtual void Draw3D() override;
	};
}