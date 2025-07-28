using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio
{
    [StructLayout(LayoutKind.Sequential)]
    public struct AudioSource
    {
        float Pitch;

        float Gain;
        float MaxGain;
        float MinGain;

        System.Numerics.Vector3 Position;
        System.Numerics.Vector3 Velocity;
        System.Numerics.Vector3 Direction;

        float MaxDistance;
        float ReferenceDistance;

        float RolloffFactor;

        float ConeOuterGain;
        float ConeInnerAngle;
        float ConeOuterAngle;

        bool Looping;
    }
}
