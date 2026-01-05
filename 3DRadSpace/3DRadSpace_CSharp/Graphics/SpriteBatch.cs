using Engine3DRadSpace.Math;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Graphics
{
	public enum SpriteBatchSortMode
	{
		/// <summary>
		/// Do not sort the sprites.
		/// </summary>
		Immediate,
		/// <summary>
		/// Sort by texture. Use this if you want to optimize the number of draw calls.
		/// </summary>
		SortedByTexture,
		/// <summary>
		/// Sort by depth. From front (0.0f) to back (-inf).
		/// </summary>
		SortedByDepth_FrontToBack,
		/// <summary>
		/// Sort by depth. From back (-inf) to front (0.0f).
		/// </summary>
		SortedByDepth_BackToFront,
	};

	public class SpriteBatch : NatPtrWrapper
	{
		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_Create")]
		extern static IntPtr _create(IntPtr graphicsDevice);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_Begin")]
		extern static void _begin(IntPtr spriteBatch, SpriteBatchSortMode mode);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_DrawNormalized")]
		extern static unsafe void _drawNorm(
			IntPtr spriteBatch,
			IntPtr texture, 
			Internal.RectangleF* coords,
			Internal.RectangleF* source,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_DrawNormalized2")]
		extern static unsafe void _drawNorm2(
			IntPtr spriteBatch,
			IntPtr texture, 
			Internal.RectangleF* coords,
			Internal.Rectangle* source,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_Draw")]
		extern static unsafe void _draw(
			IntPtr spriteBatch,
			IntPtr texture, 
			Internal.Rectangle* coords,
			Internal.Rectangle* source,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

		[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_Draw2")]
		extern static unsafe void _draw(
			IntPtr spriteBatch,
			IntPtr texture, 
			Internal.Rectangle* coords,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

		[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_SpriteBatch_DrawString")]
		extern static unsafe void _drawString(
			IntPtr spriteBatch,
			IntPtr font, 
			string text,
			System.Numerics.Vector2* pos,
			float size,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

		[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_SpriteBatch_DrawString2")]
		extern static unsafe void _drawString(
			IntPtr spriteBatch,
			IntPtr font,
			string text,
			Internal.Point* pos,
			float size,
			Math.Color* color,
			float rotation,
			FlipMode flipMode,
			float depth
		);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_End")]
        extern static void _end(IntPtr spriteBatch);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_SpriteBatch_Destroy")]
		extern static void _destroy(IntPtr spriteBatch);

		public SpriteBatch(IntPtr handle) : base(handle, _destroy)
		{
		}

		public SpriteBatch(IGraphicsDevice device) : this(_create(device.Handle))
		{
		}

		public void Begin(SpriteBatchSortMode mode)
		{
			_begin(_handle, mode);
		}

		public unsafe void DrawNormalized(
			ITexture2D texture,
			RectangleF coords,
			RectangleF source,
			Math.Color color,
			float rotation,
			FlipMode flipMode,
			float depth
		)
		{
			Internal.RectangleF argCoords = new Internal.RectangleF(coords.X, coords.Y, coords.Width, coords.Height);
			Internal.RectangleF argSource = new Internal.RectangleF(source.X, source.Y, source.Width, source.Height);

			_drawNorm(_handle, texture.Handle, &argCoords, &argSource, &color, rotation, flipMode, depth);
		}

		public unsafe void DrawNormalized(
			ITexture2D texture,
			RectangleF coords,
			Rectangle source,
			Math.Color color,
			float rotation,
			FlipMode flipMode,
			float depth
		)
		{
			Internal.RectangleF argCoords = new Internal.RectangleF(coords.X, coords.Y, coords.Width, coords.Height);
			Internal.Rectangle argSource = new Internal.Rectangle(source.X, source.Y, source.Width, source.Height);

			_drawNorm2(_handle, texture.Handle, &argCoords, &argSource, &color, rotation, flipMode, depth);
		}
		public unsafe void Draw(
			ITexture2D texture,
			Rectangle coords,
			Rectangle source,
			Math.Color color,
			float rotation,
			FlipMode flipMode,
			float depth
		)
		{
			Internal.Rectangle argCoords = new Internal.Rectangle(coords.X, coords.Y, coords.Width, coords.Height);
			Internal.Rectangle argSource = new Internal.Rectangle(source.X, source.Y, source.Width, source.Height);

			_draw(_handle, texture.Handle, &argCoords, &argSource, &color, rotation, flipMode, depth);
		}

		public unsafe void Draw(
			ITexture2D texture,
			Rectangle coords,
			Math.Color color,
			float rotation,
			FlipMode flipMode,
			float depth
		)
		{
			Internal.Rectangle argCoords = new Internal.Rectangle(coords.X, coords.Y, coords.Width, coords.Height);

			_draw(_handle, texture.Handle, &argCoords, &color, rotation, flipMode, depth);
		}

		public unsafe void DrawString(Font font, string text, Point pos, float size, Math.Color color, float rotation, FlipMode flipMode, float depth)
		{
			Internal.Point argP = new Internal.Point(pos.X, pos.Y);
			_drawString(_handle, font.Handle, text, &argP, size, &color, rotation, flipMode, depth);
		}

		public unsafe void DrawString(Font font, string text, System.Numerics.Vector2 pos, float size, Math.Color color, float rotation, FlipMode flipMode, float depth)
		{
			_drawString(_handle, font.Handle, text, &pos, size, &color, rotation, flipMode, depth);
		}

		public void End()
		{
			_end(_handle);
		}
	}
}