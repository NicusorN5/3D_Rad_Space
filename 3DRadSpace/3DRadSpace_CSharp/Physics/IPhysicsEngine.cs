using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Physics;

public class IPhysicsEngine : InstIService
{
	[DllImport("3DRadSpace.Physics.dll", EntryPoint = "E3DRSP_IPhysicsEngine_Simulate")]
	private static extern void _simulate(IntPtr physics, float dt);

	[DllImport("3DRadSpace.Physics.dll", EntryPoint = "E3DRSP_IPhysicsEngine_GetScene")]
	private static extern IntPtr _getScene(IntPtr physics);

	public void Simulate(float dt)
	{
		_simulate(_handle, dt);
	}

	public IntPtr GetScene()
	{
		return _getScene(_handle);
	}

	public IPhysicsEngine(IntPtr natPtr) : base(natPtr)
	{
	}
}
