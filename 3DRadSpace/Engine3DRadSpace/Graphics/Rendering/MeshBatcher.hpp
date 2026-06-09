#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"
#include "RenderItem.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Collects geometry submissions during a frame so they can be replayed by the rendering passes.
	/// Objects no longer draw themselves directly; they submit to the batcher, and each pass
	/// (shadow, forward, ...) replays the collected submissions in its own way.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT MeshBatcher
	{
		IGraphicsDevice* _device;

		std::vector<BatchedDraw> _draws;
		bool _beginCalled;
	public:
		MeshBatcher(IGraphicsDevice* device);

		MeshBatcher(const MeshBatcher&) = delete;
		MeshBatcher& operator=(const MeshBatcher&) = delete;

		MeshBatcher(MeshBatcher&&) noexcept = default;
		MeshBatcher& operator=(MeshBatcher&&) noexcept = default;

		/// <summary>
		/// Clears the collected submissions and prepares for a new frame.
		/// </summary>
		void Begin();

		/// <summary>
		/// Submits raw geometry plus a material effect and its forward-pass constant buffer payload.
		/// </summary>
		/// <param name="vertices">Vertex buffer.</param>
		/// <param name="indices">Index buffer.</param>
		/// <param name="material">Effect used during the forward pass.</param>
		/// <param name="forwardConstants">Pointer to the constant buffer (slot 0) payload for the forward pass. May be null.</param>
		/// <param name="forwardConstantsSize">Size, in bytes, of the forward constants payload.</param>
		/// <param name="world">World transform of the submission.</param>
		/// <param name="passType">Render pass classification.</param>
		void Submit(
			IVertexBuffer* vertices,
			IIndexBuffer* indices,
			Effect* material,
			const void* forwardConstants,
			size_t forwardConstantsSize,
			const Math::Matrix4x4& world,
			RenderPassType passType = RenderPassType::Opaque
		);

		/// <summary>
		/// Submits a mesh part. The part's transform is used as the forward constant buffer payload.
		/// </summary>
		/// <param name="meshPart">Mesh part to submit.</param>
		/// <param name="passType">Render pass classification.</param>
		void Draw(ModelMeshPart* meshPart, RenderPassType passType = RenderPassType::Opaque);

		/// <summary>
		/// Returns the collected submissions for this frame.
		/// </summary>
		const std::vector<BatchedDraw>& Items() const noexcept;

		/// <summary>
		/// Marks the end of submissions for this frame.
		/// </summary>
		void End();
	};
}
