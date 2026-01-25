namespace Engine3DRadSpace.Graphics;

public interface IGPUBuffer : IGPUResource
{
	public ulong ReadData(IntPtr ppData);
	public void SetData(IntPtr pData, ulong buffSize);
	public void EndRead();
}
