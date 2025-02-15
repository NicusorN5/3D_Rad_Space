/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Rendering/IEffectOutline.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../ModelMeshPart.hpp"
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a rendering pipeline that allows multiple rendering effects.
	/// </summary>
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

		/// <summary>
		/// Prepares the graphics pipeline for this effect.
		/// </summary>
		virtual void Begin() = 0;
		/// <summary>
		/// Submits a mesh part to this effect.
		/// </summary>
		/// <param name="part">Mesh</param>
		virtual void Draw(ModelMeshPart* part);
		/// <summary>
		/// Submits a mesh made of a index and vertex buffer to this effect.
		/// </summary>
		/// <param name="vertices">Vertices</param>
		/// <param name="indices">Incides</param>
		virtual void Draw(VertexBuffer* vertices, IndexBuffer* indices);
		/// <summary>
		/// Restores the previous states, and depending on the effect, draws all submited meshes. (Unless meshes are not batched).
		/// </summary>
		virtual void End() = 0;

		virtual ~IRenderer() = default;
	};
}