#pragma once

/// All headers[1] are included here. To be added preferably in a precompiled header for end-user projects.
/// Not to be included inside the engine itself [2].
/// [1] - Except:
/// - Headers from Internal, they're only meant to be used by the engine itself.
/// - Reflection headers, the refelction component is meant to be used by the editor that's written in C++.
/// - Legacy header, it exports C functions to the AngelScript interface.
///   Including it would also cause a circular depedency, since Legacy.hpp includes this header.
/// [2] - As already specified, this is meant for projects that use the engine as a framework.

//Engine3DRadSpace::...
#include "Color.hpp"
#include "Game.hpp"
#include "GraphicsDevice.hpp"
#include "IDrawable2D.hpp"
#include "IDrawable3D.hpp"
#include "IInitializable.hpp"
#include "ILoadable.hpp"
#include "IObject.hpp"
#include "IObject2D.hpp"
#include "IObject3D.hpp"
#include "IUpdateable.hpp"
#include "Logging.hpp"
#include "Memory.hpp"
#include "ObjectList.hpp"
#include "Viewport.hpp"
#include "Window.hpp"

//Engine3DRadSpace::Algorithms
#include "Algorithms\FixedArray.hpp"
#include "Algorithms\LevenshteinDistance.hpp"

//Engine3DRadSpace::Algorithms::Picking
#include "Algorithms\Picking\PickingRenderTargetRender.hpp"
#include "Algorithms\Picking\PickingShader.hpp"

//Engine3DRadSpace::Audio
#include "Audio\AudioBuffer.hpp"
#include "Audio\AudioEngine.hpp"
#include "Audio\AudioError.hpp"
#include "Audio\AudioSource.hpp"
#include "Audio\Sound.hpp"
#include "Audio\SoundInstance.hpp"
#include "Audio\SoundState.hpp"

//Engine3DRadSpace::Content
#include "Content\AssetFactory.hpp"
#include "Content\AssetID.hpp"
#include "Content\AssetTypeRegistration.hpp"
#include "Content\ContentManager.hpp"
#include "Content\IAsset.hpp"
#include "Content\ShaderManager.hpp"

//Engine3DRadSpace::Graphics
#include "Graphics\BlendState.hpp"
#include "Graphics\BufferUsage.hpp"
#include "Graphics\DepthStencilBuffer.hpp"
#include "Graphics\DepthStencilState.hpp"
#include "Graphics\FlipMode.hpp"
#include "Graphics\Font.hpp"
#include "Graphics\Glyph.hpp"
#include "Graphics\IDomainShader.hpp"
#include "Graphics\IFragmentShader.hpp"
#include "Graphics\IGeometryShader.hpp"
#include "Graphics\IHullShader.hpp"
#include "Graphics\IndexBuffer.hpp"
#include "Graphics\IShader.hpp"
#include "Graphics\IVertexShader.hpp"
#include "Graphics\Model3D.hpp"
#include "Graphics\ModelMesh.hpp"
#include "Graphics\ModelMeshPart.hpp"
#include "Graphics\PixelFormat.hpp"
#include "Graphics\RasterizerState.hpp"
#include "Graphics\RenderTarget.hpp"
#include "Graphics\SamplerState.hpp"
#include "Graphics\ShaderCompilationError.hpp"
#include "Graphics\ShaderFeatureLevel.hpp"
#include "Graphics\SpriteBatch.hpp"
#include "Graphics\Texture2D.hpp"
#include "Graphics\VertexBuffer.hpp"
#include "Graphics\VertexDeclarations.hpp"
#include "Graphics\VertexTopology.hpp"

//Engine3DRadSpace::Graphics::Primitives
#include "Graphics\Primitives\Box.hpp"
#include "Graphics\Primitives\Circle.hpp"
#include "Graphics\Primitives\IPrimitive.hpp"
#include "Graphics\Primitives\LineList.hpp"
#include "Graphics\Primitives\LineStrip.hpp"
#include "Graphics\Primitives\Plane.hpp"
#include "Graphics\Primitives\Sphere.hpp"

//Engine3DRadSpace::Graphics::Rendering
#include "Graphics\Rendering\ForwardRenderer.hpp"
#include "Graphics\Rendering\IEffectOutline.hpp"
#include "Graphics\Rendering\IRenderer.hpp"
#include "Graphics\Rendering\IRenderingEffect.hpp"
#include "Graphics\Rendering\LinearPixelFogEffect.hpp"
#include "Graphics\Rendering\PostProcessCollection.hpp"
#include "Graphics\Rendering\PostProcessEffect.hpp"

//Engine3DRadSpace::Graphics::Shaders
#include "Graphics\Shaders\BasicTextured.hpp"
#include "Graphics\Shaders\BlankShader.hpp"
#include "Graphics\Shaders\Blank_NoMatrix.hpp"
#include "Graphics\Shaders\SpriteShader.hpp"

//Engine3DRadSpace::Input
#include "Input\ButtonState.hpp"
#include "Input\Key.hpp"
#include "Input\Keyboard.hpp"
#include "Input\KeyState.hpp"
#include "Input\Mouse.hpp"

//Engine3DRadSpace::Logging
#include "Logging\Exception.hpp"
#include "Logging\Message.hpp"
#include "Logging\ResourceLoadingError.hpp
#include "Logging\Warning.hpp

//Engine3DRadSpace::Math
#include "Math\BoundingBox.hpp"
#include "Math\BoundingPlane.hpp"
#include "Math\BoundingSphere.hpp"
#include "Math\Math.hpp"
#include "Math\Matrix3x3.hpp"
#include "Math\Matrix4x4.hpp"
#include "Math\Point.hpp"
#include "Math\Quaternion.hpp"
#include "Math\Ray.hpp"
#include "Math\Rectangle.hpp"
#include "Math\Triangle.hpp"
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Math\Vector4.hpp"

//Engine3DRadSpace::Objects
#include "Objects\Camera.hpp"
#include "Objects\Counter.hpp"
#include "Objects\Empty.hpp"
#include "Objects\ExitFade.hpp"
#include "Objects\Fog.hpp"
#include "Objects\GForce.hpp"
#include "Objects\Skinmesh.hpp"
#include "Objects\SkyColor.hpp"
#include "Objects\Sprite.hpp"
#include "Objects\TextPrint.hpp"

//Engine3DRadSpace::Physics
#include "Physics\IPhysicsObject.hpp"
#include "Physics\PhysicsEngine.hpp"
#include "Physics\PhysicsSettings.hpp"
#include "Physics\StaticRigidbody.hpp"

//Engine3DRadSpace::Plugins
#include "Plugins\CustomObject.hpp"
#include "Plugins\EditorPlugin.hpp"

//Engine3DRadSpace::Projects
#include "Projects\Serialization.hpp"