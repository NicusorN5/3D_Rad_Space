#pragma once
#include "../../Math/Matrix4x4.hpp"
#include "RenderPassType.hpp"
#include <vector>
#include <cstddef>

namespace Engine3DRadSpace::Graphics
{
	class IVertexBuffer;
	class IIndexBuffer;
	class Effect;
}

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// A single batched, replayable draw submission. Collected by the MeshBatcher and replayed by each
	/// render pass (forward pass uses the material effect + forward constants, the shadow pass uses its
	/// own depth effect with the stored world matrix).
	/// </summary>
	struct BatchedDraw
	{
		/// <summary> Geometry vertex buffer. </summary>
		IVertexBuffer* Vertices = nullptr;
		/// <summary> Geometry index buffer. </summary>
		IIndexBuffer* Indices = nullptr;
		/// <summary> Effect used during the forward (main) pass. </summary>
		Effect* Material = nullptr;
		/// <summary> World transform of this submission. Used by passes that recompute their own matrices (e.g. shadows). </summary>
		Math::Matrix4x4 World;
		/// <summary> Constant buffer payload (slot 0) for the forward pass, captured at submit time. </summary>
		std::vector<std::byte> ForwardConstants;
		/// <summary> Classifies how this submission participates in the rendering passes. </summary>
		RenderPassType PassType = RenderPassType::Opaque;
	};
}
