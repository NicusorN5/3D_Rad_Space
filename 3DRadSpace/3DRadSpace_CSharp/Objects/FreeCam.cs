using System;
using System.Runtime.InteropServices;
using Engine3DRadSpace.Input;

namespace Engine3DRadSpace.Objects
{
	public class FreeCam : Camera
	{
		#region FFI Bindings
		private const string DLL = "3DRadSpace.FFI.dll";

		[DllImport(DLL)]
		private static extern IntPtr E3DRSP_FreeCam_Create();

		[DllImport(DLL)]
		private static extern float E3DRSP_FreeCam_GetMovementSpeed(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetMovementSpeed(IntPtr freecam, float speed);

		[DllImport(DLL)]
		[return: MarshalAs(UnmanagedType.I1)]
		private static extern bool E3DRSP_FreeCam_IsXInverted(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetXInverted(IntPtr freecam, [MarshalAs(UnmanagedType.I1)] bool invertX);

		[DllImport(DLL)]
		[return: MarshalAs(UnmanagedType.I1)]
		private static extern bool E3DRSP_FreeCam_IsYInverted(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetYInverted(IntPtr freecam, [MarshalAs(UnmanagedType.I1)] bool invertY);

		[DllImport(DLL)]
		private static extern Key E3DRSP_FreeCam_GetForwardKey(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetForwardKey(IntPtr freecam, Key key);

		[DllImport(DLL)]
		private static extern Key E3DRSP_FreeCam_GetBackwardKey(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetBackwardKey(IntPtr freecam, Key key);

		[DllImport(DLL)]
		private static extern Key E3DRSP_FreeCam_GetLeftKey(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetLeftKey(IntPtr freecam, Key key);

		[DllImport(DLL)]
		private static extern Key E3DRSP_FreeCam_GetRightKey(IntPtr freecam);

		[DllImport(DLL)]
		private static extern void E3DRSP_FreeCam_SetRightKey(IntPtr freecam, Key key);
		#endregion

		public FreeCam() : base(E3DRSP_FreeCam_Create())
		{
		}

		public float MovementSpeed
		{
			get => E3DRSP_FreeCam_GetMovementSpeed(_handle);
			set => E3DRSP_FreeCam_SetMovementSpeed(_handle, value);
		}

		public bool XInverted
		{
			get => E3DRSP_FreeCam_IsXInverted(_handle);
			set => E3DRSP_FreeCam_SetXInverted(_handle, value);
		}

		public bool YInverted
		{
			get => E3DRSP_FreeCam_IsYInverted(_handle);
			set => E3DRSP_FreeCam_SetYInverted(_handle, value);
		}

		public Key ForwardKey
		{
			get => E3DRSP_FreeCam_GetForwardKey(_handle);
			set => E3DRSP_FreeCam_SetForwardKey(_handle, value);
		}

		public Key BackwardKey
		{
			get => E3DRSP_FreeCam_GetBackwardKey(_handle);
			set => E3DRSP_FreeCam_SetBackwardKey(_handle, value);
		}

		public Key LeftKey
		{
			get => E3DRSP_FreeCam_GetLeftKey(_handle);
			set => E3DRSP_FreeCam_SetLeftKey(_handle, value);
		}

		public Key RightKey
		{
			get => E3DRSP_FreeCam_GetRightKey(_handle);
			set => E3DRSP_FreeCam_SetRightKey(_handle, value);
		}
	}
}