#include "Game.hpp"
#include "Game.h"
#include "../Objects/ObjectList.hpp"
#include "../Projects/Serialization.hpp"
#include "../Logging/Logging.hpp"
#include "GameFactory.hpp"
#include "Content/Assets/Assets.hpp"
#include "../Physics/NVPhysX/PhysicsEngine.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Native;
using namespace Engine3DRadSpace::Objects;

void Game::_initialize()
{
	AddService<IGraphicsDevice>(Device.get());

	Content = std::make_unique<Content::ContentManager>(this);

	RequireService(typeid(IAudioEngine));

	RequireService(typeid(Graphics::SpriteBatch));
	RequireService(typeid(PostProcessCollection));

	Internal::RegisterDefaultTypes(Content.get());

	_valid = true;
}

IService* Game::RequireService(const std::type_index& type)
{
	if (auto s = IGame::RequireService(type); s != nullptr) return s;

	if (typeid(IAudioEngine) == type)
	{
		if(Audio) return Audio.get();

		Audio = std::make_unique<AudioEngine>();
		AddService<IAudioEngine>(Audio.get());
		return Audio.get();
	}
	if (typeid(PostProcessCollection) == type)
	{
		if (PostProcesses) return PostProcesses.get();

		PostProcesses = std::make_unique<Graphics::Rendering::PostProcessCollection>(Device.get());
		AddService(PostProcesses.get());
		return PostProcesses.get();
	}

	if (typeid(Graphics::SpriteBatch) == type)
	{
		if (SpriteBatch) return SpriteBatch.get();

		SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
		AddService(SpriteBatch.get());
		return SpriteBatch.get();
	}

	if (typeid(Physics::IPhysicsEngine) == type)
	{
		if (Physics) return Physics.get();

		Physics = std::make_unique<Physics::NVPhysX::PhysicsEngine>(Physics::PhysicsSettings{
			.PhysicsEnabled = true,
			.Gravity = 9.81f,
			.TimeStep = 1.0f / 60.0f
			}
		);
		return Physics.get();
	}
	return nullptr;
}

Game::Game(const std::string &title, size_t width, size_t height, bool fullscreen) :
	Window(std::make_unique<Native::Window>(title, width, height)),
	Objects(std::make_unique<ObjectList>(this)),
	Keyboard(Window->GetKeyboardState()),
	Mouse(Window->GetMouseState())
{
	Device = GameFactory::CreateGraphicsDevice("", Window->NativeHandle(), width, height);
	_initialize();
}

Game::Game(Native::Window &&window) :
	Window(std::make_unique<Native::Window>(std::move(window))),
	Objects(std::make_unique<ObjectList>(this)),
	Keyboard(Window->GetKeyboardState()),
	Mouse(Window->GetMouseState())
{
	Math::Point size = Window->Size();

	Device = GameFactory::CreateGraphicsDevice("", Window->NativeHandle(), size.X, size.Y);

	_initialize();
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

	auto cmd = Device->ImmediateContext();
	cmd->SetViewport();
	cmd->Clear(ClearColor);

	Draw3D();

	PostProcesses->ApplyAll();

	Draw2D();

	cmd->Present();

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
		if (type == ObjectType::IObject3D)
		{
			(static_cast<IObject3D*>(object.get()))->Draw3D();
		}
	}
}

void Game::Draw2D()
{
	for (auto& [object, type] : *Objects)
	{
		if (type == ObjectType::IObject2D)
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

	auto viewport = Device->ImmediateContext()->GetViewport();

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

E3DRSP_Game E3DRSP_Game_Create(const char* title, size_t width, size_t height, bool fullscreen)
{
	if (title == nullptr) title = "";
	return new Game(title, width, height, fullscreen);
}

void E3DRSP_Game_Run(E3DRSP_Game game)
{
	if (game == nullptr) return;
	static_cast<Game*>(game)->Run();
}

void E3DRSP_Game_RunOneFrame(E3DRSP_Game game)
{
	if (game == nullptr) return;
	static_cast<Game*>(game)->RunOneFrame();
}

void E3DRSP_Game_Exit(E3DRSP_Game game)
{
	if (game == nullptr) return;
	static_cast<Game*>(game)->Exit();
}

bool E3DRSP_Game_WasInitialized(E3DRSP_Game game)
{
	if (game == nullptr) return false;
	return static_cast<Game*>(game)->WasInitialized();
}

bool E3DRSP_Game_WasLoaded(E3DRSP_Game game)
{
	if (game == nullptr) return false;
	return static_cast<Game*>(game)->WasLoaded();
}

E3DRSP_Ray E3DRSP_Game_GetMouseRay(
	E3DRSP_Game game,
	E3DRSP_Vector2 mousePos,
	const E3DRSP_Matrix4x4* view,
	const E3DRSP_Matrix4x4* projection
)
{
	if (game == nullptr || view == nullptr || projection == nullptr) return E3DRSP_Ray
	{
		E3DRSP_Vector3{0.0f, 0.0f, 0.0f},
		E3DRSP_Vector3{0.0f, 0.0f, 0.0f}
	};

	//Assume same memory layout
	Matrix4x4 m_view;
	memcpy_s(&m_view, sizeof(Matrix4x4), view, sizeof(E3DRSP_Matrix4x4));

	Matrix4x4 m_proj;
	memcpy_s(&m_proj, sizeof(Matrix4x4), projection, sizeof(E3DRSP_Matrix4x4));

	auto ray = static_cast<Game*>(game)->GetMouseRay(
		{ mousePos.X, mousePos.Y },
		m_view,
		m_proj
	);

	return E3DRSP_Ray
	{
		E3DRSP_Vector3{ray.Origin.X, ray.Origin.Y, ray.Origin.Z},
		E3DRSP_Vector3{ray.Direction.X, ray.Direction.Y, ray.Direction.Z},
	};
}

void E3DRSP_Game_AppendScene(E3DRSP_Game game, const char* path)
{
	if (game == nullptr) return;
	if (path == nullptr) return;
	static_cast<Game*>(game)->AppendScene(path);
}
void E3DRSP_Game_Destroy(E3DRSP_Game game)
{
	if (game == nullptr) return;
	delete static_cast<Game*>(game);
}