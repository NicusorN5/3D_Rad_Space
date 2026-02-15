#include "GameFactory.hpp"
#include "../Graphics/DirectX11/GraphicsDevice.hpp"
#include "../Graphics/Null/GraphicsDevice.hpp"
#include "../Audio/IAudioEngine.hpp"
#include "../Physics/IPhysicsEngine.hpp"
#include "../Logging/Logging.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

std::unordered_map<std::string, GameFactory::FnCreateGraphicsDevice> GameFactory::_deviceCtors;
GameFactory::FnCreateGraphicsDevice GameFactory::_fallback;

//Used to call GameFactory::ctor.
static GameFactory dummy;

GameFactory::GameFactory()
{
	auto insertCtor = []<typename Device>(const std::string &name)
	{
		_deviceCtors.insert(std::make_pair<std::string, FnCreateGraphicsDevice>(
			std::string(name),
			[](void* hwnd, size_t x, size_t y) -> std::unique_ptr<IGraphicsDevice>
			{
				return std::make_unique<Device>(hwnd, x, y);
			}
		));
	};

	//Create default GraphicsDevice instances.
	if (_deviceCtors.empty())
	{
		insertCtor.template operator()<DirectX11::GraphicsDevice>("DirectX11");
		_fallback = _deviceCtors["DirectX11"];

		insertCtor.template operator()<Null::GraphicsDevice>("Null");
	}
}

std::unique_ptr<Graphics::IGraphicsDevice> GameFactory::CreateGraphicsDevice(const std::string& name, void* hwnd, size_t x, size_t y)
{
	if (name.empty()) return _fallback(hwnd, x, y);
	else return _deviceCtors[name](hwnd, x, y);
}

void GameFactory::RegisterDevice(const std::string& name, FnCreateGraphicsDevice fn)
{
	if (name.empty() || fn == nullptr) return;

	_deviceCtors.insert(std::make_pair(name, fn));
}

void GameFactory::Begin(const std::string& title, size_t width, size_t height)
{
	if (_game) return;
	
	_game = std::make_unique<Game>(title, width, height);
}

void GameFactory::Begin(Native::Window&& window)
{
	_game = std::make_unique<Game>(std::move(window));
}

void GameFactory::AddService(std::unique_ptr<IService>&& service)
{
	auto ptr = service.release();

	if (auto audio = dynamic_cast<Audio::IAudioEngine*>(ptr); audio != nullptr)
	{
		_game->Audio.reset(audio);
		return;
	}

	if (auto physics = dynamic_cast<Physics::IPhysicsEngine*>(ptr); physics != nullptr)
	{
		_game->Physics.reset(physics);
	}
}

void GameFactory::SetFallbackGraphicsDeviceCtor(FnCreateGraphicsDevice fn)
{
	_fallback = fn;
}

std::unique_ptr<Game> GameFactory::CreateGame()
{
	return std::move(_game);
}