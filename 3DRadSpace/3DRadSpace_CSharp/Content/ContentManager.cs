using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Content
{
    public class ContentManager : InstIService
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

        internal ContentManager(IntPtr handle) : base(handle)
        {
        }

        private unsafe (IAsset, uint) _loadCall(UUID uuid, string path)
        {
            uint id;
            var ptr = _load(_service, &uuid, path, &id);

            return (new InstIAsset(ptr), id);
        }

        public (IAsset, uint) Load(ref UUID uuid, string path)
        {
            return _loadCall(uuid, path);
        }

        public void Remove(uint id)
        {
            _remove(_service, id);
        }

        public void Clear()
        {
            _clear(_service);
        }

        public ulong Count()
        {
            return _count(_service);
        }
    }
}