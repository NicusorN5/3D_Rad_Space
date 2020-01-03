﻿using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Colors the screen when screen cleaning is used. 
    /// <para>Notice the missing Update(), Draw(), EditorDraw() and Load() functions. They aren't used because only the colour is needed.</para>
    /// </summary>
    public class SkyColor : GameObject
    {
        /// <summary>
        /// The colour itself.
        /// </summary>
        public Color Color { get; set; }
        
        /// <summary>
        /// SkyColor object constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="active">Is the object active?</param>
        /// <param name="c">Color used for the screen.</param>
        public SkyColor(string name,bool active,Color c)
        {
            Name = name;
            Enabled = active;
            Color = c;
        }
        /// <summary>
        /// Generates an empty SkyColor object.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="active">Is Object active</param>
        public SkyColor(string name,bool active)
        {
            Name = name;
            Enabled = active;
            Color = Color.Black;
        }
        /// <summary>
        /// Gets the color.
        /// <para>Returns null if the object is inactive, otherwise returns this.Color .</para>
        /// </summary>
        /// <returns>Returns null if the object is inactive, otherwise returns this.Color .</returns>
        public Color? GetColor()
        {
            if (Enabled) return Color;
            else return null;
        }
    }
}