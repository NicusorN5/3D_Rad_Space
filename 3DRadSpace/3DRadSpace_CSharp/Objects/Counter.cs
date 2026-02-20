using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Counter : InstIObject
	{
		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_GetValue")]
		extern static double _getValue(IntPtr counter);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_SetValue")]
		extern static void _setValue(IntPtr counter, double value);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_GetValue")]
		extern static double _getIncrement(IntPtr counter);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_SetValue")]
		extern static void _setIncrement(IntPtr counter, double value);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_IsLoadingFromFile")]
		extern static byte _isFromFile(IntPtr counter);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_SetLoadingFromFile")]
		extern static void _setLoadingFromFile(IntPtr counter, byte loadingFromFile);

		[DllImport("3DRadSpace.Objects.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Counter_SetLoadingFromFile")]
		extern static string _getFile(IntPtr counter);

		[DllImport("3DRadSpace.Objects.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Counter_IsLoadingFromFile")]
		extern static void _setFile(IntPtr counter, string file);

		[DllImport("3DRadSpace.Objects.dll", EntryPoint = "E3DRSP_Counter_Save")]
		extern static void _save(IntPtr counter);

		public Counter() : base(_create())
		{
		}

		public double Value
		{
			get => _getValue(_handle);
			set => _setValue(_handle, value);
		}

		public double Increment
		{
			get => _getIncrement(_handle);
			set => _setIncrement(_handle, value);
		}

		public string File
		{
			get
			{
				if (_isFromFile(_handle) > 0)
				{
					return _getFile(_handle);
				}
				else return "";
			}
			set
			{
				if(value == null)
				{
					_setLoadingFromFile(_handle, 0);
					return;
				}

				_setLoadingFromFile(_handle, 1);
				_setFile(_handle, value);
			}
		}

		public void Save()
		{
			_save(_handle);
		}
	}
}
