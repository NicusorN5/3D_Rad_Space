using System.Runtime.InteropServices;
using Engine3DRadSpace.Native;
using Engine3DRadSpace.Graphics;

namespace Engine3DRadSpace;

public class Game : InstIGame
{
	private IntPtr _gameHandle = IntPtr.Zero;

	protected List<Tuple<int, object>> objects;

	[DllImport("3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??0Game@Engine3DRadSpace@@QEAA@$$QEAVWindow@1@@Z")]
	static extern private IntPtr _createGameFromWindow();

	[DllImport("3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?Run@Game@Engine3DRadSpace@@QEAAXXZ")]
	static extern private void _runGame(IntPtr gameHandle);

	public Game(string title, uint width = 800, uint height = 600) : base(IntPtr.Zero)
	{
		_gameHandle = _createGameFromWindow();
		objects = new List<Tuple<int, object>>();
		Window = new Window(title, width, height);
		Device = null;

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
