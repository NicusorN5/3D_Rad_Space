namespace Engine3DRadSpace.Graphics;

public interface IIndexBuffer : IGPUBuffer
{
	public void Set(uint index);
	public uint NumIndices();
	public IIndexBuffer CreateStaging();
}
