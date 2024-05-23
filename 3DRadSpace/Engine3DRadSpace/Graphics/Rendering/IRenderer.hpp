#pragma once
#include "../ModelMeshPart.hpp"
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IRenderer
	{
	protected:
		GraphicsDevice* _device;
		std::vector<std::unique_ptr<IRenderingEffect>> _effects;

		IRenderer(GraphicsDevice* device);
	public:
		IRenderer(const IRenderer&) = delete;
		IRenderer& operator=(const IRenderer&) = delete;

		IRenderer(IRenderer&&) noexcept = default;
		IRenderer& operator=(IRenderer&&) noexcept = default;

		virtual void Begin() = 0;
		virtual void Draw(ModelMeshPart* part);
		virtual void Draw(VertexBuffer* vertices, IndexBuffer* indices);
		virtual void End() = 0;

		virtual ~IRenderer() = default;
	};
}