using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public class InstIService : IDisposable
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IService_Destroy")]
        extern static void _destroy(IntPtr handle);
        
        protected IntPtr _service;
        bool _disposed;

        public InstIService(IntPtr handle)
        {
            _service = handle;
            _disposed = false;
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
                if (_service != 0)
                {
                    _destroy(_service);
                }
                _disposed = true;
                _service = IntPtr.Zero;
            }
        }

        ~InstIService()
        {
            Dispose(false);
        }
    }
}
