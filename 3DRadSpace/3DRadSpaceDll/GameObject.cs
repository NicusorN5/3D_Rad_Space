﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// Called when drawing the object
	/// </summary>
	/// <param name="drawn">The drawn object. Conversion will be needed.</param>
	/// <param name="spriteBatch">SpriteBatch used for drawing 2D objects</param>
	/// <param name="view">View Matrix used for 3D model drawing</param>
	/// <param name="projection">Projection Matrix used for 3D model drawing</param>
	public delegate void onDraw(object drawn, SpriteBatch spriteBatch, Matrix? view, Matrix? projection);
	/// <summary>
	/// Called when updating.
	/// </summary>
	/// <param name="updated">The updated object</param>
	/// <param name="mouse">Mouse inputs</param>
	/// <param name="keyboard">Keyboard inputs</param>
	/// <param name="time">Game time input</param>
	public delegate void onUpdate(object updated, MouseState? mouse, KeyboardState? keyboard, GameTime time);
	/// <summary>
	/// Called when a object is being removed.
	/// </summary>
	/// <param name="obj">The removed object</param>
	public delegate void onObjectDestroy(object obj);
	/// <summary>
	/// Called when a object resource is being loaded.
	/// </summary>
	/// <param name="obj">Object</param>
	public delegate void onObjectLoad(object obj);
	/// <summary>
	/// Called when a object is being unloaded.
	/// </summary>
	/// <param name="obj">Object to be unloaded</param>
	public delegate void onObjectUnload(object obj);

	/// <summary>
	/// Base class for all 3DRadSpace objects.
	/// </summary>
	public class GameObject
	{
		/// <summary>
		/// Default constructor.
		/// </summary>
		public GameObject()
		{
			Behiavours = new List<ObjectBehiavour>();
		}
		/// <summary>
		/// Object Name. Used as a string identifier.
		/// </summary>
		public string Name { get; set; }

		/// <summary>
		/// Tag object.
		/// </summary>
		public object Tag { get; set; }
		
		/// <summary>
		/// Checks if object is enabled.
		/// </summary>
		public bool Enabled { get; set; }
		/// <summary>
		/// Checks if object is being drawn.
		/// </summary>
		public bool Hidden { get; set; }
		/// <summary>
		/// Object position
		/// </summary>
		public Vector3 Position;
		/// <summary>
		/// Rotation in a Euler angles system.
		/// </summary>
		public Vector3 Rotation;

		/// <summary>
		/// Relation with other objects
		/// </summary>
		public List<ObjectBehiavour> Behiavours { get; set; }

		/// <summary>
		/// Rotation in a Quaterion system.
		/// </summary>
		public Quaternion RotationQuaternion
		{
			get
			{
				return Quaternion.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z);
			}
		}
		/// <summary>
		/// Resource file
		/// </summary>
		public string Resource { get; set; }
		/*
		{
			get
			{
				return res;
			}
			set
			{
				if (System.IO.File.Exists(@"/Content/"+value) == false) throw new System.IO.FileNotFoundException("Resource " + value + " is missing");
				else res = value;
			}
		}
		*/
		//string res;
		/// <summary>
		/// Enables object.
		/// </summary>
		public void Enable() { Enabled = true; }
		/// <summary>
		/// Disables object.
		/// </summary>
		public void Disable() { Enabled = false; }
		/// <summary>
		/// Switches object on/off state.
		/// </summary>
		public void Toggle() { Enabled = !Enabled; }
		/// <summary>
		/// Shows the object.
		/// </summary>
		public void Show() { Hidden = false; }
		/// <summary>
		/// Hides the object.
		/// </summary>
		public void Hide() { Hidden = true; }
		/// <summary>
		/// Loads the resource(s).
		/// </summary>
		public virtual void Load(ContentManager content)
		{
			OnObjectLoad?.Invoke(this);
		}
		/// <summary>
		/// Unloads the resource.
		/// </summary>

		/// <summary>
		/// Object Drawing code
		/// </summary>
		public virtual void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
		{
			OnDraw?.Invoke(this, spriteBatch, view, projection);
		}
		/// <summary>
		/// Object draw code for the 3DRadSpace editor
		/// </summary>
		public virtual void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
		{

		}
		/// <summary>
		/// Object update logic
		/// </summary>
		public virtual void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
		{
			OnUpdate?.Invoke(this, mouse, keyboard, time);
			if(_runningonce)
			{
				Enabled = false;
				_runningonce = false;
			}
		}

		/// <summary>
		/// This is specific to objects like ExitFade, NetServer,etc
		/// </summary>
		public virtual void Trigger()
		{
			Enable();
		}

		/// <summary>
		/// Called when object is being drawn on frame.
		/// </summary>
		public event onDraw OnDraw;
		/// <summary>
		/// Called when object is being updated on the update logic loop.
		/// </summary>
		public event onUpdate OnUpdate;
		/// <summary>
		/// Called when object is being deleted.
		/// </summary>
		public event onObjectDestroy OnRemoval;
		/// <summary>
		/// Called when a object resource is being loaded.
		/// </summary>
		public event onObjectLoad OnObjectLoad;

		/// <summary>
		/// Object destructor.
		/// </summary>
		~GameObject()
		{
			OnRemoval?.Invoke(this);
		}
		/// <summary>
		/// Checks if the object exists. Same as GameObject != null.
		/// </summary>
		/// <param name="o">GameObject to check.</param>
		public static implicit operator bool(GameObject o)
		{
			if (o != null) return true;
			else return false;
		}
		/// <summary>
		/// Checks if two GameObjects are equal.
		/// </summary>
		/// <param name="a">Left instance.</param>
		/// <param name="b">Right instance.</param>
		/// <returns>A boolean value representing the equality value.</returns>
		public static bool operator == (GameObject a,GameObject b)
		{
			if (ReferenceEquals(a, null))
			{
				if (ReferenceEquals(b, null)) return true;
				else return false;
			}
			return a.Equals(b);
		}
		/// <summary>
		/// The opposite of the equality operator.
		/// </summary>
		/// <param name="a">Left instance.</param>
		/// <param name="b">Right instance.</param>
		/// <returns>A boolean value representine the inequality of the two given instances.</returns>
		public static bool operator != (GameObject a,GameObject b)
		{
			return !(a == b);
		}

		/// <summary>
		/// Determines whether the specified object is equal to the current object.
		/// </summary>
		/// <param name="obj">The object to compare with the current object.</param>
		/// <returns></returns>
		public override bool Equals(object obj)
		{
			if (obj is GameObject a)
				return (a.Name == Name && a.Position == Position && a.Rotation == Rotation && a.Resource == Resource
				&& a.Hidden == Hidden && a.Enabled == Enabled && a.Behiavours == Behiavours);
			else return base.Equals(obj);
		}
		/// <summary>
		/// Returns the hash code calculated from a string representing the data inside the object.
		/// </summary>
		/// <returns>Some hash code</returns>
		public override int GetHashCode()
		{
			return (Name + " " + Position + " " + Rotation + " " + Resource + " " + Enabled + " " + Hidden).GetHashCode();
		}

		/// <summary>
		/// Returns the object's name
		/// </summary>
		/// <returns>the object's name</returns>
		public override string ToString()
		{
			return Name;
		}

		bool _runningonce = false;
		/// <summary>
		/// Runs the object one Update loop. If used on a active object it will be stopped.
		/// </summary>
		public void RunOnce()
		{
			_runningonce = true;
		}
	}
}
