#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Flags used when creating a graphics device.
	/// </summary>
	enum class GraphicsDeviceCreationOptions : unsigned int
	{
		/// <summary>
		/// Use default settings. SelectGPU_Default
		/// </summary>
		Unspecified = 0,
		/// <summary>
		/// Enable debug layers.
		/// </summary>
		Debug = 1 << 0,
		/// <summary>
		/// Default device context is singlethreaded.
		/// </summary>
		Singlethreaded = 1 << 1,
		/// <summary>
		/// Selects the GPU with the most RAM memory.
		/// </summary>
		SelectGPU_Performance = 1 << 2,
		/// <summary>
		/// Selects the GPU with least RAM memory.
		/// </summary>
		SelectGPU_Integrated = 1 << 3,
		/// <summary>
		/// Selects an software rendering device.
		/// </summary>
		SelectGPU_Software = 1 << 4,
		/// <summary>
		/// Selects the first enumerated GPU device.
		/// </summary>
		SelectGPU_Default = 1 << 5,
		/// <summary>
		/// Starts the device in fullscreen mode.
		/// </summary>
		Fullscreen = 1 << 6,
		/// <summary>
		/// Disables Alt+Enter fullscreen toggle.
		/// </summary>
		NoAltEnter = 1 << 7
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