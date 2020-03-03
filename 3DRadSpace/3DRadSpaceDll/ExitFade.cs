﻿using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// Allows loading other projects.
	/// </summary>
	public class ExitFade : GameObject
	{
		/// <summary>
		/// Main constructor of ExitFade class.
		/// </summary>
		/// <param name="name">Name of the object.</param>
		/// <param name="Path">Project to load.</param>
		/// <param name="fadecolor">Fade Color.</param>
		/// <param name="fadetime">Fade Time, measured in miliseconds.
		/// <para>Defaults to 0.</para></param>
		/// <param name="fade_type">Fades in or our.
		/// <para>true = fade in</para>
		/// <para>false = fade out</para></param>
		public ExitFade(string name, string Path, Color fadecolor,int fadetime=0,bool fade_type=true)
		{
			Name = name;
			Resource = Path;
			Fade = fadecolor;
			Time = (double)fadetime / 1000;
			initial_time = Time;
			FadeType = fade_type;
			if (FadeType) Fade = new Color(Fade,255);
			else Fade = new Color(Fade,0);
		}

		static Texture2D _blank_1x1= null;
		double _time_remaining;
		double initial_time;

		/// <summary>
		/// Project path.
		/// </summary>
		public string ProjectToLoad { get; set; }

		/// <summary>
		/// Fade color.
		/// </summary>
		public Color Fade { get; set; }

		/// <summary>
		/// Time for the fade in milliseconds (ms)
		/// </summary>
		public double Time
		{
			get
			{
				return _time_remaining;
			}
			set
			{
				_time_remaining = value;
			}
		}

		/// <summary>
		/// Toggles fade type. In or out.
		/// <para>true = fade in</para>
		/// <para>false = fade out</para>
		/// </summary>
		public bool FadeType { get; set; }

		/// <summary>
		/// When starting the object in the editor events, or scripts, this will get called.
		/// </summary>
		public override void Trigger()
		{
			Enabled = true;
			base.Trigger();
		}
		/// <summary>
		/// Draws the fading.
		/// </summary>
		/// <param name="spriteBatch">Needed for drawing the fading.</param>
		/// <param name="view">Not needed.</param>
		/// <param name="projection">Not needed.</param>
		public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
		{
			if (Enabled)
			{
				if (_blank_1x1 == null)
				{
					_blank_1x1 = new Texture2D(spriteBatch.GraphicsDevice, 1, 1);
					_blank_1x1.SetData(new Color[] { Fade });
				}
				spriteBatch.Draw(_blank_1x1, new Rectangle(0, 0, 10000, 10000), Fade);
				base.Draw(spriteBatch, view, projection);
			}
		}
		/// <summary>
		/// Updated the fade alpha timer.
		/// </summary>
		/// <param name="mouse"></param>
		/// <param name="keyboard"></param>
		/// <param name="time"></param>
		public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
		{
			if (Enabled)
			{
				_time_remaining -= time.ElapsedGameTime.TotalSeconds; //aka delta time
				//Some stupid ass formula I'm not sure it works.
				double alpha = 255 * (_time_remaining / Time); 
				Fade = new Color(Fade, (int)alpha); //recreate the color.
				if (_time_remaining <= 0) LoadProject();
				base.Update(mouse, keyboard, time);
			}
		}
		void LoadProject()
		{
			Project.UnloadObjects();
			Game.GameObjects = Project.Open(ProjectToLoad);
		}
	}
}
