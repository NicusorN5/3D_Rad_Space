using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    internal class InstIDrawable2D : IDrawable2D, IDisposable
    {
        protected IntPtr _handle;
        bool _disposed;

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable2D_Destroy")]
        extern static void _destroy(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable2D_Draw2D")]
        extern static void _draw2D(IntPtr handle);

        protected InstIDrawable2D(IntPtr handle)
        {
            _handle = handle;
            _disposed = false;
        }

        public void Draw2D()
        {
            _draw2D(_handle);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (_handle != 0)
                {
                    _destroy(_handle);
                }
                _disposed = true;
                _handle = IntPtr.Zero;
            }
        }

        ~InstIDrawable2D()
        {
            Dispose(false);
        }
    }
}
