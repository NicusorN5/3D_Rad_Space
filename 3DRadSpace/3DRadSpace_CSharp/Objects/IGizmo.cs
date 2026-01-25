namespace Engine3DRadSpace.Objects;

public interface IGizmo : IUpdateable, IDrawable3D, IDrawable2D, ILoadable
{
	public IObject Object { get; set; }
	public bool Selected { get; set; }
	public bool Is3DRenderingAllowed { get; set; }
	public bool Is2DRenderingAllowed { get; set; }
	public bool IsUpdatingAllowed { get; set; }
}