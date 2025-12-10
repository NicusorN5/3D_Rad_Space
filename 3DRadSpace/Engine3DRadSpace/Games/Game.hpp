#pragma once
#include "../Native/Window.hpp"
#include "../Core/IUpdateable.hpp"
#include "../Core/IDrawable3D.hpp"
#include "../Core/IDrawable2D.hpp"
#include "../Core/IInitializable.hpp"
#include "../Objects/IObject2D.hpp"
#include "../Objects/IObject3D.hpp"
#include "../Core/ILoadable.hpp"
#include "../Math\Matrix4x4.hpp"
#include "../Content/ContentManager.hpp"
#include "../Graphics/SpriteBatch.hpp"
#include "../Reflection/ReflectedObject.hpp"
#include "../Physics/IPhysicsEngine.hpp"
#include "../Audio/IAudioEngine.hpp"
#include "../Graphics/Rendering/PostProcessCollection.hpp"
#include "../Core/IGame.hpp"

namespace Engine3DRadSpace
{
	//class Objects::ObjectList;

	class E3DRSP_GAMES_EXPORT Game : public IGame, public IUpdateable, public IDrawable3D, public IDrawable2D, public IInitializable, public ILoadable
	{
	private:
		bool _valid = false;
		bool _running = true;
		bool _wasInitialized = false;
		bool _wasLoaded = false;

		std::optional<std::filesystem::path> _newScene;

		void _initialize();
		void _loadScene();
	public:
		Game(const std::string &title, size_t width = 800, size_t height = 600, bool fullscreen = false);
		Game(Native::Window&& window);

		Game(Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = default;
		Game& operator=(Game&&) = default;

		std::unique_ptr<Native::Window> Window;
		std::unique_ptr<Graphics::IGraphicsDevice> Device;
		std::unique_ptr<Objects::ObjectList> Objects;

		Math::Matrix4x4 View;
		Math::Matrix4x4 Projection;

		std::unique_ptr<Content::ContentManager> Content;

		std::unique_ptr<Graphics::SpriteBatch> SpriteBatch;

		Math::Color ClearColor = Math::Colors::Black;

		Input::Keyboard& Keyboard;
		Input::Mouse& Mouse;

		std::unique_ptr<Physics::IPhysicsEngine> Physics;
		std::unique_ptr<Audio::IAudioEngine> Audio;
		std::unique_ptr<Graphics::Rendering::PostProcessCollection> PostProcesses;

		IService* RequireService(const std::type_index& type);

		double Draw_dt = 0;
		double Update_dt = 0;

		void Run();
		void RunOneFrame();
		void Exit();

		bool WasInitialized() const noexcept;
		bool WasLoaded() const noexcept;

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
