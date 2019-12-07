﻿using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.IO;
using _3DRadSpaceDll;

namespace _3DRadSpace_Player
{
    public class Game1 : Microsoft.Xna.Framework.Game,IEffectFog
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        string[] Settings;
        Color ClearColor = Color.Black;
        Matrix view, projection;

        public Vector3 FogColor { get; set; }
        public bool FogEnabled { get; set; }
        public float FogEnd { get; set; }
        public float FogStart { get; set; }

        public Game1(string DebugProject)
        {
            if (DebugProject != null)
            {
                Window.Title = "Debugging - " + DebugProject;
                Content.RootDirectory = "Content";
                _3DRadSpaceDll.Game.GameObjects = Project.Open(DebugProject);
            }
            else
            {
                try { Settings = File.ReadAllLines(@"GameConfig.cfg"); }
                catch (FileNotFoundException) { }
                finally
                {
                    Window.Title = Settings[0];
                    Content.RootDirectory = Settings[1];
                }
                try
                {
                    _3DRadSpaceDll.Game.GameObjects = Project.Open(Settings[2]);
                }
                catch (FileNotFoundException)
                {
                }
            }
            graphics = new GraphicsDeviceManager(this);
        }
        protected override void Initialize()
        {
            base.Initialize();
        }
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.Load(null);
            }
        }
        protected override void UnloadContent()
        {
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.End();
            }
        }
        protected override void Update(GameTime gameTime)
        {
            MouseState mouse = Mouse.GetState();
            KeyboardState keyboard = Keyboard.GetState();
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Update(mouse, keyboard, gameTime);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script s) s.Update(mouse, keyboard, gameTime);
            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(ClearColor);
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Draw(null,out view,out projection);
                if (_3DRadSpaceDll.Game.GameObjects[i] is SkyColor s) ClearColor = s.Color;
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.Draw(spriteBatch, view, projection);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Fog f)
                {
                    FogEnabled = f.Enabled;
                    FogColor = f.FogColor;
                    FogStart = f.FogStart;
                    FogEnd = f.FogEnd;
                }
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skinmesh skinmesh)
                {
                    if(skinmesh.FogEnabled)
                    {
                        skinmesh.FogColor = FogColor;
                        skinmesh.FogStart = FogStart;
                        skinmesh.FogEnd = FogEnd;
                    }
                    skinmesh.Draw(null, view, projection);
                }
            }
            base.Draw(gameTime);
        }
    }
}
