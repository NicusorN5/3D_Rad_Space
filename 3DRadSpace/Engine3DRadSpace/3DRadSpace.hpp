#pragma once

/// All headers[1] are included here. To be added preferably in a precompiled header for end-user projects.
/// Not to be included inside the engine itself [2].
/// [1] - Except:
/// - Headers from Internal, they're only meant to be used by the engine itself.
/// - Reflection headers, the refelction component is meant to be used by the editor that's written in C++.
/// - Legacy header, it exports C functions to the AngelScript interface.
///   Including it would also cause a circular depedency, since Legacy.hpp includes this header.
/// [2] - As already specified, this is meant for projects that use the engine as a framework.

//Header files ordered alphabetically and by namespaces.


//Engine3DRadSpace
#include "Core/Libs.hpp"

//Engine3DRadSpace::Algorithms
#include "Core\Algorithms\FixedArray.hpp"

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
#include "Content\ContentManager.hpp"
#include "Content\IAsset.hpp"
#include "Content\ShaderManager.hpp"

//Engine3DRadSpace::Content::Assets
#include "Content\Assets\Font.hpp"
#include "Content\Assets\Model3D.hpp"
#include "Content\Assets\SkyboxAsset.hpp"

//Engine3DRadSpace::Graphics
#include "Graphics\BlendState.hpp"
#include "Graphics\BufferUsage.hpp"
#include "Graphics\DepthStencilBuffer.hpp"
#include "Graphics\DepthStencilState.hpp"
#include "Graphics\FlipMode.hpp"
#include "Graphics\Glyph.hpp"
#include "Graphics\IDomainShader.hpp"
#include "Graphics\IFragmentShader.hpp"
#include "Graphics\IGeometryShader.hpp"
#include "Graphics\IHullShader.hpp"
#include "Graphics\IndexBuffer.hpp"
#include "Graphics\IShader.hpp"
#include "Graphics\IVertexShader.hpp"
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
#include "Graphics\Primitives\CubeMapSkybox.hpp"
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
#include "Graphics\Shaders\SkyboxShader.hpp"
#include "Graphics\Shaders\SpriteShader.hpp"

//Engine3DRadSpace::Input
#include "Input\ButtonState.hpp"
#include "Input\Key.hpp"
#include "Input\Keyboard.hpp"
#include "Input\KeyState.hpp"
#include "Input\Mouse.hpp"

//Engine3DRadSpace::Logging
#include "Core\Logging\Exception.hpp"
#include "Core\Logging\Message.hpp"
#include "Core\Logging\AssetLoadingError.hpp"
#include "Core\Logging\Warning.hpp"

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
#include "Objects\ObjectList.hpp"
#include "Objects\Skinmesh.hpp"
#include "Objects\SkyColor.hpp"
#include "Objects\Sprite.hpp"
#include "Objects\TextPrint.hpp"

//Engine3DRadSpace::Native
#include "Native\LibraryLoader.hpp"
#include "Native\Window.hpp"

//Engine3DRadSpace::Physics
#include "Physics\GForce.hpp"
#include "Physics\IPhysicsObject.hpp"
#include "Physics\PhysicsEngine.hpp"
#include "Physics\PhysicsSettings.hpp"

//Engine3DRadSpace::Plugins
#include "Plugins\CustomObject.hpp"
#include "Plugins\EditorPlugin.hpp"
#include "Plugins\PluginInfo.hpp"

//Engine3DRadSpace::Projects
#include "Projects\Serialization.hpp"