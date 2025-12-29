using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Content
{
    public class ContentManager : IDisposable
    {
        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_ContentManager_Load")]
        unsafe static extern IntPtr _load(IntPtr content, Reflection.UUID* uuid, string path, uint* id);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_ContentManager_Reload")]
        static extern void _reload(IntPtr content, uint id);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_ContentManager_Remove")]
        static extern void _remove(IntPtr content, uint id);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_ContentManager_Clear")]
        static extern void _clear(IntPtr content);

        [DllImport("3DRadSpace.Content.dll", EntryPoint = "E3DRSP_ContentManager_Clear")]
        static extern ulong _count(IntPtr content);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IService_Destroy")]
        static extern ulong _destroy(IntPtr content);

        IntPtr _content;
        bool _disposed;

        internal ContentManager(IntPtr handle)
        {
            _content = handle;
            _disposed = false;
        }

        private unsafe (IAsset, uint) _loadCall(UUID uuid, string path)
        {
            uint id;
            var ptr = _load(_content, &uuid, path, &id);

            return (new InstIAsset(ptr), id);
        }

        public (IAsset, uint) Load(ref UUID uuid, string path)
        {
            return _loadCall(uuid, path);
        }

        public void Remove(uint id)
        {
            _remove(_content, id);
        }

        public void Clear()
        {
            _clear(_content);
        }

        public ulong Count()
        {
            return _count(_content);
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
                if (_content != 0)
                {
                    _destroy(_content);
                }
                _disposed = true;
                _content = IntPtr.Zero;
            }
        }

        ~ContentManager()
        {
            Dispose(false);
        }
    }
}