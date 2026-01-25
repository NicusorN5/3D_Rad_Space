namespace Engine3DRadSpace.Graphics;

public struct FaceOperation
{
	public StencilOperation StencilFail;
	public StencilOperation DepthFail;
	public StencilOperation PassOp;
	public ComparisonFunction Function;
};
