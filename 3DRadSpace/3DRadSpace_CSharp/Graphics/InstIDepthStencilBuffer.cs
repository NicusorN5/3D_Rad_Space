using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
    public class InstIDepthStencilBuffer : InstGPUBuffer, IDepthStencilBuffer
    {
        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IDepthStencilBuffer_GetDepthTextureHandle")]
        extern static IntPtr _depthHandle(IntPtr depthBuffer);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IDepthStencilBuffer_GetDepthTexture")]
        extern static IntPtr _depthTexture(IntPtr depthBuffer);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IDepthStencilBuffer_CloneDepthTexture")]
        extern static IntPtr _cloneDepth(IntPtr depthBuffer);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IDepthStencilBuffer_Destroy")]
        extern static void _destroy(IntPtr depthBuffer);

        public InstIDepthStencilBuffer(IntPtr handle) : base(handle) 
        {
        }

        public IntPtr GetDepthTextureHandle()
        {
            return _depthHandle(_handle);
        }
        public ITexture2D GetDepthTexture()
        {
            return new InstITexture2D(_depthTexture(_handle));
        }

        public ITexture2D CloneDepthTexture()
        {
            return new InstITexture2D(_cloneDepth(_handle));
        }
    }
}
