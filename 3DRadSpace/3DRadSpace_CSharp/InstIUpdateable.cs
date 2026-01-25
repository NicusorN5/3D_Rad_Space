using System.Runtime.InteropServices;

namespace Engine3DRadSpace;

public abstract class InstIUpdateable : NatPtrWrapper, IUpdateable
{
    [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IUpdateable_Update")]
    extern static void _update(IntPtr handle);

    [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IUpdateable_Destroy")]
    extern static void _destroy(IntPtr handle);

    internal InstIUpdateable(IntPtr handle) : base(handle, _destroy)
    {
    }

    public void Update()
    {
        _update(_handle);
    }
}
