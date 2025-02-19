using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	public class Game
	{
		private IntPtr _gameHandle = IntPtr.Zero;
		private bool _disposed;

		bool _valid;
		bool _running = true;

		double u_dt;
		double d_dt;

		protected List<Tuple<int, object>> objects;

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "??0Game@Engine3DRadSpace@@QEAA@$$QEAVWindow@1@@Z")]
		static extern private IntPtr _createGameFromWindow();

		[DllImport("Engine3DRadSpace.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?Run@Game@Engine3DRadSpace@@QEAAXXZ")]
		static extern private void _runGame(IntPtr gameHandle);

		public Game(string title, uint width = 800, uint height = 600, bool fullscreen = false)
		{
			objects = new List<Tuple<int, object>>();
			Window = new Window(title, width, height);
			Device = new GraphicsDevice(Window.NativeHandle, width, height);
		}

		public Window Window { get; private set; }
		public GraphicsDevice Device { get; private set; }

		public void Run()
		{
			_runGame(_gameHandle);
		}
	}
}
