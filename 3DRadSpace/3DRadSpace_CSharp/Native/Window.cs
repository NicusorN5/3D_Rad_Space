using System.Runtime.InteropServices;
using Engine3DRadSpace.Input;
using Engine3DRadSpace.Internal;
using System;

namespace Engine3DRadSpace.Native
{
	public class Window : NatPtrWrapper
	{
		[DllImport("Engine3DRadSpace.Native.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Window_Create")]
		private static extern IntPtr window_Create(string title, uint width, uint height);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_NativeHandle")]
		private static extern IntPtr window_NativeHandle(IntPtr window);

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_ProcessMessages")]
		private static extern void window_ProcessMessages(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_GetMouseState")]
        private static extern Mouse window_GetMouseState(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_GetKeyboardState")]
        private static extern Keyboard window_GetKbState(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_Size")]
        private static extern Point window_Size(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_RectangleF")]
        private static extern RectangleF window_RF(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_Rectangle")]
        private static extern Rectangle window_R(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_IsFocused")]
        private static extern bool window_IsFocused(IntPtr window);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_SetMousePosition")]
        private static extern void window_SetMousePosition(IntPtr window, ref Point p);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_SetTitle")]
        private static extern bool window_SetTitle(IntPtr window, string title);

        [DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Window_Destroy")]
        private static extern void window_Destroy(IntPtr window);
		public Window(string title, uint width, uint height) : base(window_Create(title, width, height), window_Destroy)
		{
		}

		public IntPtr NativeHandle
		{
			get
			{
				return window_NativeHandle(_handle);
			}
		}

		public void ProcessMessages()
		{
			window_ProcessMessages(_handle);
		}

		public Mouse MouseState
		{
			get
			{
				return window_GetMouseState(_handle);
			}
		}

		public Keyboard KeyboardState
		{
			get
			{
				return window_GetKbState(_handle);
			}
		}

		public Point Size
		{
			get
			{
				return window_Size(_handle);
			}
		}

		public Rectangle RectangleF
		{
			get
			{
				return window_R(_handle);
			}
		}

        public RectangleF Rectangle
        {
            get
            {
                return window_RF(_handle);
            }
        }

		public bool IsFocused
		{
			get
			{
				return window_IsFocused(_handle);
			}
		}

		public void SetMousePosition(Point p)
		{
            window_SetMousePosition(_handle, ref p);
		}

		public void SetTitle(string title)
		{
			window_SetTitle(_handle, title);
		}
    }
}
