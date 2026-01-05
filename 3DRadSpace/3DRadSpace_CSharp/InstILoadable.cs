

using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class InstILoadable : NatPtrWrapper, ILoadable
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_ILoadable_Load2")]
        extern static void _load(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ILoadable_Load2")]
        extern static void _load2(IntPtr handle, string path);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_ILoadable_Destroy")]
        extern static void _destroy(IntPtr handle);

        protected InstILoadable(IntPtr handle) : base(handle, _destroy)
        {
        }

        public void Load()
        {
            _load(_handle);
        }

        public void Load(string path)
        {
            _load2(_handle, path);
        }
    }
}
