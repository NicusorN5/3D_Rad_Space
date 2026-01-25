using System.Runtime.InteropServices;
using Engine3DRadSpace.Native;
using Engine3DRadSpace.Graphics;

namespace Engine3DRadSpace;

public class Game : InstIGame
{
	private IntPtr _gameHandle = IntPtr.Zero;

	protected List<Tuple<int, object>> objects;

	[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??0Game@Engine3DRadSpace@@QEAA@$$QEAVWindow@1@@Z")]
	static extern private IntPtr _createGameFromWindow();

	[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?Run@Game@Engine3DRadSpace@@QEAAXXZ")]
	static extern private void _runGame(IntPtr gameHandle);

	public Game(string title, uint width, uint height, bool fullscreen) : base(IntPtr.Zero)
	{
		objects = new List<Tuple<int, object>>();
		Window = new Window(title, width, height);
		Device = null;
		
	}
	public Game(string title) : this(title, 800, 600, false) {  }
	public Game(string title, uint width, uint height) : this(title, width, height, false)
	{
		//TODO: Actually use Game(string, uint, uint), not Game(Window&&) !
		_gameHandle = _createGameFromWindow();
	}

	public Window Window { get; private set; }
	public IGraphicsDevice Device { get; private set; }

	public IntPtr InstanceHandle
	{
		get => _gameHandle;
	}

	public void Run()
	{
		_runGame(_gameHandle);
	}
}
