using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
    public class InstIBlendState : InstGPUResource, IBlendState
    {
        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IBlendState_BlendFactor")]
        extern static Color _blendFactor(IntPtr blendState);

        [DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_IBlendState_SampleMask")]
        extern static uint _sampleMask(IntPtr blendState);

        public Color BlendFactor()
        {
            return _blendFactor(_handle);
        }

        public uint SampleMask()
        {
            return _sampleMask(_handle);
        }

        public InstIBlendState(IntPtr handle) : base(handle)
        {
        }
    }
}
