namespace Engine3DRadSpace;

public interface ILoadable : IPtrWrapper
{
	public void Load();
	public void Load(string path);
}
