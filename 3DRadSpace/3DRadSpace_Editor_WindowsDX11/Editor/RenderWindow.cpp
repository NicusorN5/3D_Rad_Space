#include "RenderWindow.hpp"
#include <Engine3DRadSpace/Graphics/Font.hpp>
#include "../Frontend/Settings.hpp"
#include <Engine3DRadSpace/Graphics/Primitives/Box.hpp>
#include <Engine3DRadSpace/ObjectList.hpp>

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	editorWindow(parent)
{
}

void RenderWindow::Initialize()
{
	std::vector<VertexPositionColor> axisLines =
	{
		//+X
		VertexPositionColor{Vector3(0,0,0),Colors::Red},
		VertexPositionColor{Vector3(500,0,0),Colors::Red},
		//-X
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(-500,0,0),Colors::White},
		//+Y
		VertexPositionColor{Vector3(0,0,0),Colors::Green},
		VertexPositionColor{Vector3(0,500,0),Colors::Green},
		//-Y
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,-500,0),Colors::White},
		//+Z
		VertexPositionColor{Vector3(0,0,0),Colors::Blue},
		VertexPositionColor{Vector3(0,0,500),Colors::Blue},
		//-Z
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,0,-500),Colors::White},
	};

	constexpr int halfNumLines = 25;

	std::vector<VertexPositionColor> dLines;
	for (int i = -halfNumLines; i <= halfNumLines; i++)
	{
		if (i == 0) continue;
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,halfNumLines), Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,-halfNumLines), Colors::Gray });

		dLines.push_back(VertexPositionColor{ Vector3(halfNumLines, 0, float(i)), Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(-halfNumLines, 0, float(i)), Colors::Gray });
	}

	axis = std::make_unique<Primitives::Lines>(Device.get(), axisLines);
	grid = std::make_unique<Primitives::Lines>(Device.get(), dLines);
	Camera.LookMode = Camera::CameraMode::UseLookAtCoordinates;
	Camera.FarPlaneDistance = 10'000.0f;

	_pickingShader = std::make_unique<PickingShader>(Device.get());
}

Model3D *fish = nullptr;

void RenderWindow::Load(Content::ContentManager *content)
{

}

void RenderWindow::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	zoom = mouse.ScrollWheel();
	if (zoom < -4.0f) zoom = -4.0f;

	if (mouse.LeftButton() == ButtonState::Pressed && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = mouse.Position();
		Window->SetMousePosition(screenCenter);

		Vector2 mouseDelta = (Vector2)(screenCenter - mousePos) * float(dt);
		cameraPos -= mouseDelta * Settings::CameraSensitivity.Value;

		cameraPos.Y = std::clamp<float>(
			cameraPos.Y,
			-std::numbers::pi_v<float> / 2.f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.f - std::numeric_limits<float>::epsilon()
		);
	}

	if (mouse.RightButton() == ButtonState::Pressed)
	{
		auto ray = GetMouseRay(mouse.Position(), View, Projection);

		for (auto& obj : *Objects)
		{
			if (obj.InternalType == ObjectList::ObjectInstance::ObjectType::IObject3D)
			{
				auto dst = static_cast<IObject3D*>(obj.Object.get())->Intersects(ray);
				if (dst.has_value())
				{
					cursor3D = ray.Origin + ray.Direction * dst.value();
					if (std::isnan(cursor3D.X) || std::isnan(cursor3D.Y) || std::isnan(cursor3D.Z))
					{
						cursor3D = Vector3::Zero();
					}
				}
			}
		}

		//_keyboardTest = true;
	}
	//else _keyboardTest = false;

	
	if(keyboard.IsKeyDown(Key::Space))
	{
		_keyboardTest = true;
	}
	else _keyboardTest = false;
	

	Quaternion q = Quaternion::FromYawPitchRoll(-cameraPos.Y, 0, 0) * Quaternion::FromYawPitchRoll(0, -cameraPos.X, 0);
	Camera.Position = cursor3D + Vector3::UnitZ().Transform(q) * (zoom + 5);
	Camera.LookAt = cursor3D;
}

void RenderWindow::Draw(Matrix4x4 &view, Matrix4x4 &projection, double dt)
{
	Camera.Draw(view, projection, dt);

	axis->Transform = Matrix4x4::CreateTranslation(cursor3D);
	axis->Draw(View, Projection, dt);

	if (Settings::ShowGrid.Value)
	{
		grid->Draw(View, Projection, dt);
	}

	if (_keyboardTest)
	{
	}

	//Main rendering pass
	for(auto &obj : *Objects)
	{
		switch(obj.InternalType)
		{
		case ObjectList::ObjectInstance::ObjectType::IObject2D:
				static_cast<IObject2D *>(obj.Object.get())->EditorDraw(SpriteBatch.get(), dt, false);
				break;
			case ObjectList::ObjectInstance::ObjectType::IObject3D:
				static_cast<IObject3D *>(obj.Object.get())->EditorDraw(View, Projection, dt, false);
				break;
			default:
				break;
		}
	}
}

void RenderWindow::Draw(Graphics::SpriteBatch* spriteBatch, double dt)
{
}

bool RenderWindow::IsFocused() const
{
	return editorWindow == GetForegroundWindow();
}

void RenderWindow::Reset3DCursor()
{
	cursor3D = Vector3::Zero();
}

RenderWindow::~RenderWindow()
{
}