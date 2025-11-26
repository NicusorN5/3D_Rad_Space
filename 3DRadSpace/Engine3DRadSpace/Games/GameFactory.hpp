#pragma once
#include "../Graphics/IGraphicsDevice.hpp"
#include "../Native/Window.hpp"

namespace Engine3DRadSpace
{
	class Game;
	/// <summary>
	/// Factory class for Game instances. Sets services, GraphicsDevice, AudioEngine, PhysicsEngine, etc...
	/// </summary>
	/// <remarks>
	/// A Game instance can still be constructed without this, but it will fallback to provided defaults.
	/// </remarks>
	class E3DRSP_GAMES_EXPORT GameFactory
	{
	public:
		typedef std::unique_ptr<Graphics::IGraphicsDevice>(*FnCreateGraphicsDevice)(void* hwnd, size_t x, size_t y);
	private:
		static std::unordered_map<std::string, FnCreateGraphicsDevice> _deviceCtors;
		static FnCreateGraphicsDevice _fallback;

		std::unique_ptr<Game> _game;
	public:
		GameFactory();

		GameFactory(const GameFactory&) = delete;
		GameFactory(GameFactory&&) = delete;

		GameFactory& operator=(const GameFactory&) = delete;
		GameFactory& operator=(GameFactory&&) = delete;

		/// <summary>
		/// Creates a Graphics device.
		/// </summary>
		/// <param name="name">Named backend. If empty, first element in _deviceCtors is called.</param>
		/// <returns></returns>
		static std::unique_ptr<Graphics::IGraphicsDevice> CreateGraphicsDevice(const std::string &name, void* hwnd, size_t x, size_t y);

		static void RegisterDevice(const std::string& name, FnCreateGraphicsDevice fn);

		void Begin(const std::string& title, size_t width, size_t height, bool fullscreen);
		void Begin(Native::Window&& window);

		void AddService(std::unique_ptr<IService>&& service);

		static void SetFallbackGraphicsDeviceCtor(FnCreateGraphicsDevice fn);

		std::unique_ptr<Game> CreateGame();
	};
}