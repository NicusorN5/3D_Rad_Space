namespace Engine3DRadSpace.Graphics;

public interface IVertexBuffer : IGPUBuffer, IPtrWrapper
{
	public ulong TotalSize { get; }
	public ulong StructSize { get; }
	public ulong NumVertices { get; }
	public IVertexBuffer CreateStaging();
}
