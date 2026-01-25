using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class ObjectList : NatPtrWrapper
{
	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_Create")]
	extern static IntPtr _create(IntPtr game);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_Add")]
	extern static uint _add(IntPtr list, IntPtr obj);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_FindByID")]
	extern static IntPtr _findByID(IntPtr list, uint id);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_FindByName", CharSet = CharSet.Ansi)]
	extern static IntPtr _findByName(IntPtr list, string name);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_RemoveByID")]
	extern static void _removeByID(IntPtr list, uint id);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_RemoveByName", CharSet = CharSet.Ansi)]
	extern static void _removeByName(IntPtr list, string name);

	[DllImport("Engine3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectList_Destroy")]
	extern static void _destroy(IntPtr list);

	public uint Add(IntPtr obj)
	{
		return _add(_handle, obj);
	}

	public IntPtr Find(uint id)
	{
		return _findByID(_handle, id);
	}

	public IntPtr Find(string name)
	{
		return _findByName(_handle, name);
	}

	public void Remove(uint id)
	{
		_removeByID(_handle, id);
	}

	public void Remove(string name)
	{
		_removeByName(_handle, name);
	}

	public ObjectList(IPtrWrapper game) : base(_create(game.Handle), _destroy)
	{
	}

	public ObjectList(IntPtr natPtr) : base(natPtr, _destroy)
	{
	}
}
