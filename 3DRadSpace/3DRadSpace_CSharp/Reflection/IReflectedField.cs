namespace Engine3DRadSpace.Reflection;

public interface IReflectedField
{
	ulong TypeHash { get; }
	string FieldName { get; }
	string FieldDesc { get; }
	ulong TypeSize { get; }
	ulong FieldOffset { get; }
	IntPtr Get(IntPtr objPtr);
	void Set(IntPtr objPtr, IntPtr value);
	IntPtr DefaultValue { get; }
}
