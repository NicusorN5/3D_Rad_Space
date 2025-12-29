

using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class IntIUpdateable : IUpdateable, IDisposable
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IUpdateable_Update")]
        extern static void _update(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IUpdateable_Destroy")]
        extern static void _destroy(IntPtr handle);

        protected IntPtr _handle;
        bool _disposed;

        internal IntIUpdateable(IntPtr handle)
        {
            _handle = handle;
            _disposed = false;
        }

        public void Update()
        {
            _update(_handle);
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

        ~IntIUpdateable()
        {
            Dispose(false);
        }
    }
}
