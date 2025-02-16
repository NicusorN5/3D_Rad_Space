/// ------------------------------------------------------------------------------------------------
/// File:   Game.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "Window.hpp"
#include "IUpdateable.hpp"
#include "IDrawable3D.hpp"
#include "IDrawable2d.hpp"
#include "IInitializable.hpp"
#include "IObject2D.hpp"
#include "IObject3D.hpp"
#include "ILoadable.hpp"
#include "Math\Matrix4x4.hpp"
#include "Content/ContentManager.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "Reflection/ReflectedObject.hpp"
#include "Physics/PhysicsEngine.hpp"
#include "Audio/AudioEngine.hpp"
#include "Graphics/Rendering/PostProcessCollection.hpp"

namespace Engine3DRadSpace
{
	class ObjectList;
	class DLLEXPORT Game : public IUpdateable, public IDrawable3D, public IDrawable2D, public IInitiializable, public ILoadable
	{
	private:
		bool _valid = false;
		bool _running = true;
		bool _wasInitialized = false;
		bool _wasLoaded = false;

		std::optional<std::filesystem::path> _newScene;

		void _loadScene();
	public:
		Game(const std::string &title, unsigned width = 800, unsigned height = 600, bool fullscreen = false);
		Game(Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

		std::unique_ptr<Window> Window;
		std::unique_ptr<GraphicsDevice> Device;
		std::unique_ptr<ObjectList> Objects;

		Math::Matrix4x4 View;
		Math::Matrix4x4 Projection;

		std::unique_ptr<Content::ContentManager> Content;

		std::unique_ptr<Graphics::SpriteBatch> SpriteBatch;

		Color ClearColor = Colors::Black;

		Input::Keyboard& Keyboard;
		Input::Mouse& Mouse;

		std::unique_ptr<Physics::PhysicsEngine> Physics;
		std::unique_ptr<Audio::AudioEngine> Audio;
		std::unique_ptr<Graphics::Rendering::PostProcessCollection> PostProcesses;

		double Draw_dt = 0;
		double Update_dt = 0;

		void Run();
		void RunOneFrame();
		void Exit();

		bool WasInitialized() const noexcept;
		bool WasLoaded() const noexcept;

		void RequestPhysicsInitialization(const Math::Vector3& gravity, double timeStep = 1.0 / 60.0);
		void RequestAudioInitialization();

		Math::Ray GetMouseRay(const Math::Vector2& mousePosition, const Math::Matrix4x4& view, const Math::Matrix4x4& projection);

		virtual void Initialize() override;
		virtual void Load() override;
		/// <summary>
		/// Loads a scene from file.
		/// </summary>
		/// <param name="path">3drsp file.</param>
		virtual void Load(const std::filesystem::path &path) override;

		virtual void Update() override;
		virtual void Draw3D() override;
		virtual void Draw2D() override;

		void AppendScene(const std::filesystem::path& path);

		~Game() override;
	};
}
