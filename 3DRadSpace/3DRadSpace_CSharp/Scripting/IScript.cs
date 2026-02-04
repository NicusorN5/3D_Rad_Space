namespace Engine3DRadSpace.Scripting;

/// <summary>
/// Base interface for dynamically compiled C# scripts.
/// Scripts implementing this interface can be instantiated and managed by the engine.
/// Matches the C++ IScript interface (inherits from IUpdateable).
/// </summary>
public interface IScript : IUpdateable
{
    /// <summary>
    /// Gets the object that this script is attached to.
    /// Provides access to delta time, graphics device, and other engine resources.
    /// </summary>
    IObject? Object { get; }

	/// <summary>
	/// Called when this script is added to the ScriptEngine.
	/// </summary>
	void Start();

	/// <summary>
	/// Called when this script is removed from the ScriptEngine.
	/// </summary>
	void End();
}




