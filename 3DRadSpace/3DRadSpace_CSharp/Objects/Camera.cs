using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Camera : InstIObject3D, ICamera
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_GetNormal")]
		extern static Vector3 _getNormal(IntPtr camera);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetNormal")]
		extern static unsafe void _setNormal(IntPtr camera, Vector3* normal);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_GetAspectRatio")]
		extern static float _getAspectRatio(IntPtr camera);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetAspectRatio")]
		extern static void _setAspectRatio(IntPtr camera, float aspectRatio);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_GetFOV")]
		extern static float _getFOV(IntPtr camera);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetFOV")]
		extern static void _setFOV(IntPtr camera, float fov);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_GetNPD")]
		extern static float _getNPD(IntPtr camera);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetNPD")]
		extern static void _setNPD(IntPtr camera, float npd);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_GetFPD")]
		extern static float _getFPD(IntPtr camera);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetFPD")]
		extern static void _setFPD(IntPtr camera, float fpd);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Camera_SetLookAt")]
		extern static unsafe void _setLookAt(IntPtr camera, Vector3* lookAt);

		private InstICamera _icamera;

		public Camera() : base(_create())
		{
			_icamera = new InstICamera(Handle);
		}

		public Camera(IntPtr instance) : base(instance)
		{
			_icamera = new InstICamera(Handle);
		}

		public unsafe Vector3 Normal
		{
			get => _getNormal(_handle);
			set => _setNormal(_handle, &value);
		}

		public float AspectRatio
		{
			get => _getAspectRatio(_handle);
			set => _setAspectRatio(_handle, value);
		}

		public float FieldOfView
		{
			get => _getFOV(_handle);
			set => _setFOV(_handle, value);
		}

		public float NearPlaneDistance
		{
			get => _getNPD(_handle);
			set => _setNPD(_handle, value);
		}

		public float FarPlaneDistance
		{
			get => _getFPD(_handle);
			set => _setFPD(_handle, value);
		}
		public unsafe void SetLookAt(Vector3 value)
		{
			_setLookAt(_handle, &value);
		}

		public Matrix4x4 GetViewMatrix()
		{
			return _icamera.GetViewMatrix();
		}

		public Matrix4x4 GetProjectionMatrix()
		{
			return _icamera.GetProjectionMatrix();
		}
	}
}
