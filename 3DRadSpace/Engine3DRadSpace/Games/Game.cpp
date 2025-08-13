#include "Game.hpp"
#include "../Objects/ObjectList.hpp"
#include "../Projects/Serialization.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Native;

Game::Game(const std::string &title, unsigned width, unsigned height, bool fullscreen) :
	Window(std::make_unique<Native::Window>(title, width, height)),
	Objects(std::make_unique<Engine3DRadSpace::ObjectList>(this)),
	Keyboard(Window->GetKeyboardState()),
	Mouse(Window->GetMouseState())
{
	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(),width,height);
	Content = std::make_unique<Content::ContentManager>(this);
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	PostProcesses = std::make_unique<Graphics::Rendering::PostProcessCollection>(Device.get());
	Audio = std::make_unique<AudioEngine>();
	_valid = true;
}

Game::Game(Native::Window &&window) :
	Window(std::make_unique<Native::Window>(std::move(window))),
	Objects(std::make_unique<Engine3DRadSpace::ObjectList>(this)),
	Keyboard(Window->GetKeyboardState()),
	Mouse(Window->GetMouseState())
{
	Math::Point size = Window->Size();

	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(), size.X, size.Y);
	Content = std::make_unique<Content::ContentManager>(this);
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	PostProcesses = std::make_unique<Graphics::Rendering::PostProcessCollection>(Device.get());
	Audio = std::make_unique<AudioEngine>();
	_valid = true;
}

void Game::Run()
{
	Initialize();
	_wasInitialized = true;

	Load();
	_wasLoaded = true;

	while (_running && Window->NativeHandle() != nullptr)
	{	
		Window->ProcessMessages();
		RunOneFrame();
	}
}

void Game::RunOneFrame()
{
	auto ts_u1 = std::chrono::high_resolution_clock::now();

	PostProcesses->DisableAll(); //to be re-enabled by the objects
	Audio->Update();
	Update();
	auto ts_u2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	Update_dt = uDiff.count();

	auto ts_d1 = std::chrono::high_resolution_clock::now();

	this->Device->SetViewport();
	this->Device->Clear(ClearColor);

	Draw3D();

	PostProcesses->ApplyAll();

	Draw2D();

	Device->Present();

	auto ts_d2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
	Draw_dt = dDiff.count();
}

void Game::Exit()
{
	_running = false;
}

bool Game::WasInitialized() const noexcept
{
	return _wasInitialized;
}

bool Game::WasLoaded() const noexcept
{
	return _wasLoaded;
}

void Game::RequestPhysicsInitialization(const Vector3 &gravity, double timeStep)
{
	if (!Physics)
	{
		Physics = std::make_unique<PhysicsEngine>(
			Physics::PhysicsSettings
			{
				.PhysicsEnabled = true,
				.Gravity = gravity,
				.TimeStep = timeStep
			}
		);
	}
}

void Game::RequestAudioInitialization()
{
	if (!Audio)
	{
		Audio = std::make_unique<AudioEngine>();
	}
}

Game::~Game()
{
	Exit();
}


void Game::Load()
{
	for (auto& [object, type] : *Objects)
	{
		object->Load();
	}
}

void Game::Load(const std::filesystem::path& path)
{
	_newScene = path;
}

void Game::_loadScene()
{
	this->Objects->Clear();
	AppendScene(_newScene.value());
	_newScene = std::nullopt;
}

void Game::Update()
{
	for (auto& [object, type] : *Objects)
	{
		object->Update();
	}

	if(_newScene.has_value()) _loadScene();
}

void Game::Draw3D()
{
	for (auto& [object, type] : *Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject3D)
		{
			(static_cast<IObject3D*>(object.get()))->Draw3D();
		}
	}
}

void Game::Draw2D()
{
	for (auto& [object, type] : *Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject2D)
		{
			(static_cast<IObject2D*>(object.get()))->Draw2D();
		}
	}
}

void Game::AppendScene(const std::filesystem::path& path)
{
	bool r = Projects::Serializer::LoadProject(this->Objects.get(), this->Content.get(), path);
	if(!r) throw Logging::Exception("Failed to load project " + path.string());
}

void Game::Initialize()
{
	for (auto& [object, type] : *Objects)
	{
		object->InternalInitialize(this);
		object->Initialize();
	}
}

Ray Game::GetMouseRay(const Vector2 &mousePosition, const Matrix4x4 &view, const Matrix4x4 &projection)
{
	Vector3 nearPoint = Vector3(mousePosition.X, mousePosition.Y, 0.0f);
	Vector3 farPoint = Vector3(mousePosition.X, mousePosition.Y, 1.0f);

	auto viewport = Device->GetViewport();

	nearPoint = viewport.Unproject(nearPoint, projection, view, Matrix4x4());
	farPoint = viewport.Unproject(farPoint, projection, view, Matrix4x4());
	Vector3 direction = farPoint - nearPoint;
	direction.Normalize();

	return Ray
	{
		.Origin = nearPoint,
		.Direction = direction
	};
}