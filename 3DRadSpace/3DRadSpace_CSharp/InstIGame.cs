using Engine3DRadSpace.Content;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
    internal class InstIGame : IGame, IDisposable
    {
        protected IntPtr _game;
        bool _disposed;

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IGame_Exit")]
        private static extern void _exit(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IGame_WasInitialized")]
        private static extern bool _wasInitialized(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IGame_WasLoaded")]
        private static extern bool _wasLoaded(IntPtr handle);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IGame_AppendScene", CharSet = CharSet.Ansi)]
        private static extern bool _appendScene(IntPtr handle, string path);

        [DllImport("3DRadSpace.Core.dll", EntryPoint = "E3DRSP_IGame_Destroy")]
        private static extern void _destroy(IntPtr handle);

        internal InstIGame(IntPtr handle)
        {
            _game = handle;
            _disposed = false;
        }

        public void Exit()
        {
            _exit(_game);
        }

        public bool WasInitialized
        {
            get
            {
                return _wasInitialized(_game);
            }
        }

        public bool WasLoaded
        {
            get
            {
                return _wasLoaded(_game);
            }
        }

        public void AppendScene(string path)
        {
            _appendScene(_game, path);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (_game != 0)
                {
                    _destroy(_game);
                }
                _disposed = true;
                _game = IntPtr.Zero;
            }
        }

        ~InstIGame()
        {
            Dispose(false);
        }
    }
}
