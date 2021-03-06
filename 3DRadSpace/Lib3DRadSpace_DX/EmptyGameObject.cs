﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// BaseGameObject but with a implementation of SaveF(...) and LoadF(...)
    /// </summary>
    public class EmptyGameObject : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="pos"></param>
        /// <param name="rot"></param>
        /// <param name="s"></param>
        public EmptyGameObject(string name, bool enabled, Vector3 pos, Vector3 rot, Vector3 s)
        {
            Name = name;
            Enabled = enabled;
            Position = pos;
            RotationEuler = rot;
            Scale = Scale;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(List<byte> buff, ref int position, out IGameObject result)
        {
            result = null;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        public override void SaveF(List<byte> buff, ref int position)
        {
            
        }
    }
}
