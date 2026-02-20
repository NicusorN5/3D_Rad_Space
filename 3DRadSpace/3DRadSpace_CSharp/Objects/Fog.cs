using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Fog : InstIObject
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_GetFogBegin")]
		extern static float _getFogBegin(IntPtr fog);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_SetFogBegin")]
		extern static void _setFogBegin(IntPtr fog, float fogBegin);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_GetFogEnd")]
		extern static float _getFogEnd(IntPtr fog);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_SetFogEnd")]
		extern static void _setFogEnd(IntPtr fog, float fogBegin);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_GetFogColor")]
		extern static Color _getFogColor(IntPtr fog);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Fog_SetFogColor")]
		extern static unsafe void _setFogColor(IntPtr fog, Color* color);

		public Fog() : base(_create())
		{
		}

		public float FogBegin
		{
			get => _getFogBegin(_handle);
			set => _setFogBegin(_handle, value);
		}

		public float FogEnd
		{
			get => _getFogEnd(_handle);
			set => _setFogEnd(_handle, value);
		}

		public unsafe Color FogColor
		{
			get => _getFogColor(_handle);
			set => _setFogColor(_handle, &value);
		}
	}
}
