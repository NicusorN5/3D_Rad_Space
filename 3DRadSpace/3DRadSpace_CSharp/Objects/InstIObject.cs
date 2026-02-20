using Engine3DRadSpace.Graphics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstIObject : InstIUpdateable, IObject
{
	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_GetUUID")]
	extern static Reflection.UUID _getUUID(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_GetGizmo")]
	extern static IntPtr _getGizmo(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_GetGraphicsDeviceHandle")]
	extern static IntPtr _getGDevice(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_GetGame")]
	extern static IntPtr _getGame(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_Enable")]
	extern static void _enable(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_Disable")]
	extern static void _disable(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_Switch")]
	extern static byte _switch(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_IsEnabled")]
	extern static byte _isEnabled(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_Show")]
	extern static void _show(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_Hide")]
	extern static void _hide(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_SwitchVisibility")]
	extern static byte _switchVisibility(IntPtr obj);

	[DllImport("3DRadSpace.dll", EntryPoint = "E3DRSP_IObject_IsVisible")]
	extern static byte _isVisible(IntPtr obj);

	[DllImport("3DRadSpace.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IObject_GetName")]
	extern static string _getName(IntPtr obj);

	[DllImport("3DRadSpace.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IObject_SetName")]
	extern static void _setName(IntPtr obj, string name);

	InstIInitializable _initializable;
	InstILoadable _loadable;

	public InstIObject(IntPtr handle) : base(handle)
	{
		_initializable = new InstIInitializable(handle);
		_loadable = new InstILoadable(handle);
	}

	public string Name
	{
		get => _getName(_handle);
		set => _setName(_handle, value);
	}

	public bool Enabled
	{
		get => _isEnabled(_handle) > 0;
		set
		{
			if (value)
			{
				_enable(_handle);
			}
			else
			{
				_disable(_handle);
			}
		}
	}

	public bool Visible
	{
		get => _isVisible(_handle) > 0;
		set
		{
			if (value)
			{
				_show(_handle);
			}
			else
			{
				_hide(_handle);
			}
		}
	}

	public void Enable()
	{
		_enable(_handle);
	}

	public void Disable()
	{
		_disable(_handle);
	}

	public bool Switch()
	{
		return _switch(_handle) > 0;
	}

	public void Show()
	{
		_show(_handle);
	}

	public void Hide()
	{
		_hide(_handle);
	}

	public bool SwitchVisibility()
	{
		return _switchVisibility(_handle) > 0;
	}

	public Reflection.UUID UUID => _getUUID(_handle);

	public IGame Game => new InstIGame(_getGame(_handle));
	public IGraphicsDevice GraphicsDevice => new InstIGraphicsDevice(_getGDevice(_handle));
	public IGizmo Gizmo => new InstIGizmo(_getGizmo(_handle));

	public void Initialize()
	{
		_initializable.Initialize();
	}

	public void Load()
	{
		_loadable.Load();
	}

	public void Load(string path)
	{
		_loadable.Load(path);
	}

	public override void Dispose()
	{
		base.Dispose();
		_initializable.Dispose();
		_loadable.Dispose();
	}
}
