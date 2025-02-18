/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/BufferUsage.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once

namespace Engine3DRadSpace::Graphics
{		
	enum class BufferUsage : unsigned int
	{
		/// <summary>
		/// Read and write access by the GPU. Same as D3D11_USAGE_DEFAULT.
		/// </summary>
		ReadWriteGPU,
		/// <summary>
		/// Can only be read by the GPU. Same as D3D11_USAGE_IMMUTABLE.
		/// </summary>
		ReadOnlyGPU,
		/// <summary>
		/// Accessible by both the GPU (read only) and the CPU (write only). Same as D3D11_USAGE_DYNAMIC.
		/// </summary>
		ReadOnlyGPU_WriteOnlyCPU,
		/// <summary>
		/// Only supports data transfer (copy) from the GPU to the CPU.
		/// </summary>
		Staging,
	};
}