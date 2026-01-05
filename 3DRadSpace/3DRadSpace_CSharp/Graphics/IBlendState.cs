using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Graphics
{
    public interface IBlendState : IPtrWrapper, IGPUResource
    {
        public Color BlendFactor();
        public uint SampleMask();
    }
}
