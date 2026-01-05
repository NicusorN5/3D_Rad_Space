using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class InstIDrawable2D : NatPtrWrapper, IDrawable2D
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable2D_Destroy")]
        extern static void _destroy(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable2D_Draw2D")]
        extern static void _draw2D(IntPtr handle);

        protected InstIDrawable2D(IntPtr handle) : base(handle, _destroy)
        {
        }

        public void Draw2D()
        {
            _draw2D(_handle);
        }
    }
}
