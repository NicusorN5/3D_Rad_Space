using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class TextPrint : InstIObject2D
	{
		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_TextPrint_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_TextPrint_GetFontID")]
		extern static uint _getFontID(IntPtr textPrint);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_TextPrint_SetFontID")]
		extern static void _setFontID(IntPtr textPrint, uint id);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_TextPrint_GetColor")]
		extern static Color _getColor(IntPtr textPrint);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_TextPrint_SetColor")]
		extern static unsafe void _setColor(IntPtr textPrint, Color* color);

		[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_TextPrint_GetText")]
		extern static string _getText(IntPtr textPrint);

		[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_TextPrint_SetText")]
		extern static void _setText(IntPtr textPrint, string text);

		public TextPrint() : base(_create())
		{
		}

		public uint FontID
		{
			get => _getFontID(_handle);
			set => _setFontID(_handle, value);
		}

		public unsafe Color Color
		{
			get => _getColor(_handle);
			set => _setColor(_handle, &value);
		}

		public string Text
		{
			get => _getText(_handle);
			set => _setText(_handle, value);
		}
	}
}
