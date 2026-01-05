namespace Engine3DRadSpace.Graphics
{
	public interface IVertexShader : IPtrWrapper
	{
		public Reflection.IReflectedField[] GetInputLayout();
	}
}
