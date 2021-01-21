﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Allows drawing of 3D objects. Practically a container for some Matrix structs.
    /// </summary>
    public class Camera : BaseGameObject
    {

        /// <summary>
        /// Camera object constructor.
        /// </summary>
        /// <param name="name">Object name.</param>
        /// <param name="enabled">Checks if the camera will affect the drawing matrices.</param>
        /// <param name="pos">Camera position.</param>
        /// <param name="rot">Camera rotation quaternion.</param>
        /// <param name="up">Camera up direction. A normalized vector perpendicular to the surface the camera is standing on.</param>
        /// <param name="ar">Aspect ratio.</param>
        /// <param name="fov">FOV in radians.</param>
        /// <param name="npd">Near plane distance.</param>
        /// <param name="fpd">Far plane distance.</param>
        public Camera(string name,bool enabled,Vector3 pos,Vector3 rot,Vector3 up,Vector2 ar,float fov ,float npd = 0.01f,float fpd = 500f)
        {
            Name = name;
            Enabled = enabled;
            Position = pos;
            Rotation = Quaternion.CreateFromYawPitchRoll(rot.Y,rot.X,rot.Z);
            AspectRatio = ar;
            FOV = fov;
            NearPlaneDistance = npd;
            FarPlaneDistance = fpd;
            Up = up;
            LookAtLocation = false;
        }

        /// <summary>
        /// Camera up director. A normalized vector perpendicular to the surface the camera is standing on.
        /// </summary>
        public Vector3 Up;
        /// <summary>
        /// Field of view in radians.
        /// </summary>
        public float FOV;
        /// <summary>
        /// Game window resolution / aspect ratio.
        /// </summary>
        public Vector2 AspectRatio;

        /// <summary>
        /// Minimum drawing distance.
        /// </summary>
        public float NearPlaneDistance;

        /// <summary>
        /// Maximum drawing distance.
        /// </summary>
        public float FarPlaneDistance;

        /// <summary>
        /// Makes the camera object look at a specific point rather than using a rotation.
        /// </summary>
        public bool LookAtLocation;

        /// <summary>
        /// Toggles 2D elements like sprites, textprints, etc
        /// </summary>
        public bool Allow2DSprites;

        /// <summary>
        /// Camera look-at position.
        /// </summary>
        public Vector3 Target
        {
            get
            {
                if (LookAtLocation == false) return Position + Vector3.Transform(Vector3.UnitZ, Matrix.CreateFromQuaternion(Rotation));
                else return _target;
            }
            set
            {
                if (LookAtLocation) _target = value;
                else throw new InvalidOperationException("Cannot set the camera target location when the camera is using a quaternion.");
            }
        }
        Vector3 _target;
        /// <summary>
        /// Camera View Matrix.
        /// </summary>
        public Matrix View
        {
            get
            {
                if (!LookAtLocation) return Matrix.CreateLookAt(Position, Target, Up);
                else return Matrix.CreateLookAt(Position, _target, Up);
            }
        }
        /// <summary>
        /// Camera projection Matrix.
        /// </summary>
        public Matrix Projection
        {
            get
            {
                return Matrix.CreatePerspectiveFieldOfView(FOV, AspectRatio.X / AspectRatio.Y, NearPlaneDistance, FarPlaneDistance);
            }
        }
        /// <summary>
        /// Bounding frustrum generated by the camera object.
        /// </summary>
        public BoundingFrustum CameraFrustum
        {
            get
            {
                return new BoundingFrustum(View * Projection);
            }
        }
        /// <summary>
        /// Affects the drawing matrices.
        /// </summary>
        /// <param name="time">Not used.</param>
        /// <param name="frustrum">Not used.</param>
        /// <param name="view">Output value.</param>
        /// <param name="projection">Output value.</param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            view = View;
            projection = Projection;
        }
    }
}