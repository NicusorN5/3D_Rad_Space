using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
    public class Cone : InstIObject3D
    {
        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_Create")]
        extern static IntPtr _create();

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_GetColor")]
        extern static Color _getColor(IntPtr cone);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_SetColor")]
        extern static unsafe void _setColor(IntPtr cone, Color* color);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_GetRadius")]
        extern static float _getRadius(IntPtr cone);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_SetRadius")]
        extern static void _setRadius(IntPtr cone, float radius);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_GetHeight")]
        extern static float _getHeight(IntPtr cone);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_SetHeight")]
        extern static void _setHeight(IntPtr cone, float height);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_GetResolution")]
        extern static uint _getResolution(IntPtr cone);

        [DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_OCone_SetResolution")]
        extern static void _setResolution(IntPtr cone, uint resolution);

        public Cone() : base(_create())
        {
        }

        public unsafe Color Color
        {
            get => _getColor(_handle);
            set => _setColor(_handle, &value);
        }

        public float Radius
        {
            get => _getRadius(_handle);
            set => _setRadius(_handle, value);
        }
        public float Height
        {
            get => _getHeight(_handle);
            set => _setHeight(_handle, value);
        }

        public uint Resolution
        {
            get => _getResolution(_handle);
            set => _setResolution(_handle, value);
        }
    }
}
