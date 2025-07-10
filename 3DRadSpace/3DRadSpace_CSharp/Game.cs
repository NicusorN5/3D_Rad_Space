using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	public class Game
	{
		private IntPtr _gameHandle = IntPtr.Zero;

		protected List<Tuple<int, object>> objects;

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??0Game@Engine3DRadSpace@@QEAA@$$QEAVWindow@1@@Z")]
		static extern private IntPtr _createGameFromWindow();

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?Run@Game@Engine3DRadSpace@@QEAAXXZ")]
		static extern private void _runGame(IntPtr gameHandle);

		public Game(string title, uint width, uint height, bool fullscreen)
		{
			objects = new List<Tuple<int, object>>();
			Window = new Window(title, width, height);
			Device = new GraphicsDevice(Window.NativeHandle, width, height);
		}
		public Game(string title) : this(title, 800, 600, false) {  }
		public Game(string title, uint width, uint height) : this(title, width, height, false) { }

		public Window Window { get; private set; }
		public GraphicsDevice Device { get; private set; }

		public void Run()
		{
			_runGame(_gameHandle);
		}
	}
}
