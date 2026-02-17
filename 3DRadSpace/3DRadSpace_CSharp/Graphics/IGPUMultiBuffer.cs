namespace Engine3DRadSpace.Graphics
{
    public interface IGPUMultiBuffer : IGPUResource
    {
        public ulong ReadData(ulong subresource, IntPtr ppData);
        public void SetData(ulong subresource, IntPtr pData, ulong buffSize);
        public void EndRead(ulong subresource);
    }
}
