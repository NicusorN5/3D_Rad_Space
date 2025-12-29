

using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class InstILoadable : ILoadable, IDisposable
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_ILoadable_Load2")]
        extern static void _load(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ILoadable_Load2")]
        extern static void _load2(IntPtr handle, string path);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_ILoadable_Destroy")]
        extern static void _destroy(IntPtr handle);

        protected IntPtr _handle;
        bool _disposed;

        internal InstILoadable(IntPtr handle)
        {
            _handle = handle;
            _disposed = false;
        }

        public void Load()
        {
            _load(_handle);
        }

        public void Load(string path)
        {
            _load2(_handle, path);
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

        ~InstILoadable()
        {
            Dispose(false);
        }
    }
}
