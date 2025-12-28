#pragma once

enum E3DRSP_BufferUsage
{
	/// <summary>
	/// Read and write access by the GPU. Same as D3D11_USAGE_DEFAULT.
	/// </summary>
	ED3RSP_BufferUsage_ReadWriteGPU,
	/// <summary>
	/// Can only be read by the GPU. Same as D3D11_USAGE_IMMUTABLE.
	/// </summary>
	ED3RSP_BufferUsage_ReadOnlyGPU,
	/// <summary>
	/// Accessible by both the GPU (read only) and the CPU (write only). Same as D3D11_USAGE_DYNAMIC.
	/// </summary>
	ED3RSP_BufferUsage_ReadOnlyGPU_WriteOnlyCPU,
	/// <summary>
	/// Only supports data transfer (copy) from the GPU to the CPU.
	/// </summary>
	ED3RSP_BufferUsage_Staging,
};