using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Input;

public class Keyboard
{
	private IntPtr _kb;

	internal Keyboard(IntPtr kb)
	{
		_kb = kb;
	}

	[DllImport("3DRadSpace.Input.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Keyboard_IsKeyUp")]
	private static extern bool isKeyUp(IntPtr kb, Key k);

	[DllImport("3DRadSpace.Input.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Keyboard_IsKeyDown")]
	private static extern bool isKeyDown(IntPtr kb, Key k);

	[DllImport("3DRadSpace.Input.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Keyboard_IsAnyKeyDown")]
	private static extern bool isAny(IntPtr kb);

	[DllImport("3DRadSpace.Input.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Keyboard_At")]
	private static extern KeyState at(IntPtr kb, Key k);

	public bool IsKeyUp(Key k)
	{
		return isKeyUp(_kb, k);
	}

	public bool IsKeyDown(Key k)
	{
		return isKeyDown(_kb, k);
	}

	public bool IsAnyKeyDown(Key k)
	{
		return isAny(_kb);
	}

	public KeyState this[Key k]
	{
		get => at(_kb, k);
	}
}
