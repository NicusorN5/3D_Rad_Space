using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Reflection
{
	internal class InstIReflectedField : NatPtrWrapper, IReflectedField
	{
		[DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_Destroy")]
		extern static void _destroy(IntPtr instance);

		[DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_TypeHash")]
		extern static ulong _hash(IntPtr instance);

		[DllImport("3DRadSpace.Reflection.dll",CharSet = CharSet.Ansi,  EntryPoint = "E3DRSP_IReflectedField_FieldName")]
		extern static string _name(IntPtr instance);

		[DllImport("3DRadSpace.Reflection.dll",CharSet = CharSet.Ansi,  EntryPoint = "E3DRSP_IReflectedField_FieldDesc")]
		extern static string _desc(IntPtr instance);

        [DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_TypeSize")]
        extern static ulong _size(IntPtr instance);

        [DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_FieldOffset")]
		extern static ulong _offset(IntPtr instance);

		[DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_Get")]
		extern static IntPtr _get(IntPtr instance, IntPtr objectPtr);

		[DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_Set")]
		extern static void _set(IntPtr instance, IntPtr objectPtr, IntPtr value);

		[DllImport("3DRadSpace.Reflection.dll", EntryPoint = "E3DRSP_IReflectedField_DefaultValue")]
		extern static IntPtr _default(IntPtr instance);

		public InstIReflectedField(IntPtr ptr) : base(ptr, _destroy)
		{
		}

		public ulong TypeHash
		{
			get
			{
				return _hash(_handle);
			}
		}
		public string FieldName
		{
			get
			{
				return _name(_handle);
			}
		}
		public string FieldDesc
		{
			get
			{
				return _desc(_handle);
			}
		}
		public ulong TypeSize
		{
			get
			{
				return _size(_handle);
			}
		}
		public ulong FieldOffset
		{
			get
			{
				return _offset(_handle);
			}
		}
		public IntPtr Get(IntPtr objPtr)
		{
			return _get(_handle, objPtr);
		}
		public void Set(IntPtr objPtr, IntPtr value)
		{
			_set(_handle, objPtr, value);
		}
		public IntPtr DefaultValue
		{
			get
			{
				return _default(_handle);
			}
		}
	}
}
