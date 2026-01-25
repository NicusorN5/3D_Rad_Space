namespace Engine3DRadSpace;

public interface IGame
{
	public void Exit();
	bool WasInitialized { get; }
	bool WasLoaded { get; }
	void AppendScene(string path);
}
