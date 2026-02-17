using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
    public class InstITexture3D : InstGPUMultiBuffer, ITexture3D
    {
        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_Size")]
        extern static UPoint3 _size(IntPtr texture3D);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_Width")]
        extern static uint _width(IntPtr texture3D);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_Width")]
        extern static uint _height(IntPtr texture3D);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_Depth")]
        extern static uint _depth(IntPtr texture3D);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_CreateStaging")]
        extern static IntPtr _createStaging(IntPtr texture3D);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ITexture3D_GetViewHandle")]
        extern static IntPtr _getViewHandle(IntPtr texture3D);

        public InstITexture3D(IntPtr handle) : base(handle) 
        {
        }

        public UPoint3 Size => _size(_handle);

        public uint Width => _width(_handle);

        public uint Height => _height(_handle);

        public uint Depth => _depth(_handle);

        public ITexture3D CreateStaging()
        {
            return new InstITexture3D(_createStaging(_handle));
        }

        public nint GetViewHandle()
        {
            return _getViewHandle(_handle);
        }
    }
}
