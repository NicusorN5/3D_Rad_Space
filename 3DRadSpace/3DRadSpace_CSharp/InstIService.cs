using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
    public abstract class InstIService : NatPtrWrapper
    {
        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IService_Destroy")]
        extern static void _destroy(IntPtr handle);
        
        protected InstIService(IntPtr handle) : base(handle, _destroy)
        {
        }
    }
}
