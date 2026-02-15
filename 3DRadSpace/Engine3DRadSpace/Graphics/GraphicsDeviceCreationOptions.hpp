#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Flags used when creating a graphics device.
	/// </summary>
	enum class GraphicsDeviceCreationOptions : unsigned int
	{
		Unspecified = 0,
		Debug = 1 << 0,
		Singlethreaded = 1 << 1,
		SelectGPU_Performance = 1 << 2,
		SelectGPU_Integrated = 1 << 3,
		SelectGPU_Software = 1 << 4,
		SelectGPU_Default = 1 << 5,
		Fullscreen = 1 << 6
	};

	constexpr GraphicsDeviceCreationOptions operator|(GraphicsDeviceCreationOptions a, GraphicsDeviceCreationOptions b)
	{
		return static_cast<GraphicsDeviceCreationOptions>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
	}

	constexpr GraphicsDeviceCreationOptions& operator|=(GraphicsDeviceCreationOptions &a, GraphicsDeviceCreationOptions b)
	{
		a = a | b;
		return a;
	}

	constexpr GraphicsDeviceCreationOptions operator&(GraphicsDeviceCreationOptions a, GraphicsDeviceCreationOptions b)
	{
		return static_cast<GraphicsDeviceCreationOptions>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
	}

	constexpr GraphicsDeviceCreationOptions& operator&=(GraphicsDeviceCreationOptions &a, GraphicsDeviceCreationOptions b)
	{
		a = a & b;
		return a;
	}

	constexpr GraphicsDeviceCreationOptions operator~(GraphicsDeviceCreationOptions a)
	{
		return static_cast<GraphicsDeviceCreationOptions>(~static_cast<unsigned int>(a));
	}
}