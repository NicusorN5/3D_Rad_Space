using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
    public interface IGame
    {
        public void Exit();
        bool WasInitialized { get; }
        bool WasLoaded { get; }
        void AppendScene(string path);
    }
}
