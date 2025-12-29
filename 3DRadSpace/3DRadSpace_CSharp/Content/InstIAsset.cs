using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Content
{
    internal class InstIAsset : IAsset, IDisposable
    {
        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_IAsset_GetUUID")]
        static extern UUID _getUUID(IntPtr asset);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_IAsset_FileExtension")]
        static extern string _fileExtension(IntPtr asset);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_IAsset_Destroy")]
        static extern void _destroy(IntPtr asset);

        internal InstIAsset(IntPtr asset)
        {
            _asset = asset;
            _disposed = false;
        }

        IntPtr _asset;
        bool _disposed;

        public UUID UUID
        {
            get
            {
                return _getUUID(_asset);
            }
        }

        public string FileExtension
        {
            get
            {
                return _fileExtension(_asset);
            }
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
                if (_asset != 0)
                {
                    _destroy(_asset);
                }
                _disposed = true;
                _asset = IntPtr.Zero;
            }
        }

        ~InstIAsset()
        {
            Dispose(false);
        }
    }
}
