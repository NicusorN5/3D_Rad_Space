using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class ExitFade : InstIObject2D
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ExitFade_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Camera_GetProjectPath")]
		extern static string _getProjectPath(IntPtr exitFade);

		[DllImport("3DRadSpace.Objects.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Camera_SetProjectPath")]
		extern static void _setProjectPath(IntPtr exitFade, string path);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ExitFade_GetFadeColor")]
		extern static Color _getColor(IntPtr exitFade);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ExitFade_SetFadeColor")]
		extern static unsafe void _setColor(IntPtr exitFade, Color* color);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ExitFade_GetFadeTime")]
		extern static float _getFadeTime(IntPtr exitFade);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ExitFade_SetFadeColor")]
		extern static void _setFadeTime(IntPtr exitFade, float fadeTime);

		public ExitFade() : base(_create())
		{
		}

		public string ProjectPath
		{
			get => _getProjectPath(_handle);
			set => _setProjectPath(_handle, value);
		}

		public unsafe Color FadeColor
		{
			get => _getColor(_handle);
			set => _setColor(_handle, &value);
		}

		public float FadeTime
		{
			get => _getFadeTime(_handle);
			set => _setFadeTime(_handle, value);
		}
	}
}
