using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    internal class InstIDrawable3D : IDrawable3D, IDisposable
    {
        protected IntPtr _handle;
        bool _disposed;

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable3D_Destroy")]
        extern static void _destroy(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IDrawable3D_Draw3D")]
        extern static void _draw3D(IntPtr handle);

        protected InstIDrawable3D(IntPtr handle)
        {
            _handle = handle;
            _disposed = false;
        }

        public void Draw3D()
        {
            _draw3D(_handle);
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

        ~InstIDrawable3D()
        {
            Dispose(false);
        }
    }
}
