

using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class InstIInitializable : IInitializable, IDisposable
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IInitializable_Initialize")]
        extern static void _initialize(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IInitializable_Destroy")]
        extern static void _destroy(IntPtr handle);

        protected IntPtr _handle;
        bool _disposed;

        internal InstIInitializable(IntPtr handle)
        {
            _handle = handle;
            _disposed = false;
        }

        public void Initialize()
        {
            _initialize(_handle);
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

        ~InstIInitializable()
        {
            Dispose(false);
        }
    }
}
