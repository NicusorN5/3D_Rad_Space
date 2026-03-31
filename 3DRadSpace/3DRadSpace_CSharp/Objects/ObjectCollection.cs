using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Objects
{
	public class ObjectCollection : NatPtrWrapper, ICollection<IObject>
	{
		public bool IsReadOnly => false;

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Destroy")]
		extern static void _destroy(IntPtr collection);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Add")]
		extern static void _add(IntPtr collection, IntPtr item);

		public void Add(IObject item)
		{
			_add(Handle, item.Handle);
		}

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Clear")]
		extern static void _clear(IntPtr collection);

		public void Clear()
		{
			_clear(Handle);
		}

		public bool Contains(IObject item)
		{
			for (int i = 0; i < Count; i++)
			{
				if (this[i] == item)
					return true;
			}
			return false;
		}

		public void CopyTo(IObject[] array, int arrayIndex)
		{
			for (int i = 0; i < Count; i++)
			{
				array[arrayIndex + i] = this[i];
			}
		}

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Remove")]
		extern static void _remove(IntPtr collection, IntPtr item);

		public bool Remove(IObject item)
		{
			_remove(Handle, item.Handle);
			return true;
		}

		public IEnumerator<IObject> GetEnumerator()
		{
			return (IEnumerator<IObject>)this;
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_At")]
		extern static IntPtr _at(IntPtr collection, int idx);

		IObject this[int idx]
		{
			get
			{
				return new InstIObject(_at(Handle, idx));
			}
		}

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_ObjectCollection_Count")]
		extern static int _count(IntPtr collection);

		public int Count => _count(Handle);

		public ObjectCollection() : base(_create(), _destroy)
		{
		}

		public ObjectCollection(IntPtr instance) : base(instance, _destroy)
		{
		}
	}
}
