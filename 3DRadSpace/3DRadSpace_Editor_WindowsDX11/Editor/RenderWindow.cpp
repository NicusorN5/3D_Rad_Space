#include "RenderWindow.hpp"
#include <Engine3DRadSpace/Graphics/Font.hpp>
#include "../Frontend/Settings.hpp"
#include <Engine3DRadSpace/Graphics/Primitives/Box.hpp>
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Objects/Gizmos/IGizmo.hpp>
#include <Engine3DRadSpace\Objects\Gizmos.hpp>

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Native::Window(hInstance, parent)),
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

	axis = std::make_unique<Primitives::LineList>(Device.get(), axisLines);
	grid = std::make_unique<Primitives::LineList>(Device.get(), dLines);

	Camera.InternalInitialize(this);
	Camera.LookMode = Camera::CameraMode::UseLookAtCoordinates;
	Camera.FarPlaneDistance = 1000.0f;

	//_picking = std::make_unique<PickingRenderTargetRender>(Device.get());
}

void RenderWindow::Load()
{
	_font = std::make_unique<Font>(Device.get(), "Data//Fonts//Arial.ttf");
}

Vector2 mouseDelta;

void RenderWindow::Update()
{
	for(auto &obj : *Objects)
	{
		auto gizmo = obj.Object->GetGizmo();
		if(gizmo != nullptr)
		{
			gizmo->Object = obj.Object.get();
			gizmo->Update();
		}
	}

	zoom = Mouse.ScrollWheel();
	if (zoom < -4.0f) zoom = -4.0f;

	if (Mouse.LeftButton() == ButtonState::Pressed && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = Mouse.Position();
		Window->SetMousePosition(screenCenter);

		mouseDelta = (Vector2)(screenCenter - mousePos) * float(Update_dt);
		//mouseDelta.Y = 0;
		cameraPos -= mouseDelta * Settings::CameraSensitivity.Value;

		cameraPos.Y = std::clamp<float>(
			cameraPos.Y,
			-std::numbers::pi_v<float> / 2.f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.f - std::numeric_limits<float>::epsilon()
		);
	}

	if (Mouse.RightButton() == ButtonState::Pressed)
	{
		auto ray = GetMouseRay(Mouse.Position(), View, Projection);

		for (auto& obj : *Objects)
		{
			if (obj.InternalType == ObjectType::IObject3D)
			{
				auto dst = static_cast<IObject3D*>(obj.Object.get())->Intersects(ray);
				if (dst.has_value())
				{
					cursor3D = ray.Origin + (ray.Direction * dst.value());
					_selectedObject = obj.Object.get();
					if (std::isnan(cursor3D.X) || std::isnan(cursor3D.Y) || std::isnan(cursor3D.Z))
					{
						cursor3D = Vector3::Zero();
					}
				}
			}
		}

		_requestedPicking = true;
		_pickingCoords = Mouse.Position();
	}
	//else _keyboardTest = false;

	
	if(Keyboard.IsKeyDown(Key::Space))
	{
		_keyboardTest = true;
	}
	else _keyboardTest = false;
	
	Quaternion m = Quaternion::FromYawPitchRoll(cameraPos.X, cameraPos.Y, 0);
	//auto m = Matrix4x4::CreateRotationX(-cameraPos.Y) * Matrix4x4::CreateRotationY(-cameraPos.X);
	//auto m = Matrix4x4::CreateRotationYawPitchRoll(-cameraPos.Y, -cameraPos.X, 0);
	Camera.Position = cursor3D + Vector3::UnitZ().Transform(m) * (zoom + 5);
	Camera.LookAt = cursor3D;
}

void RenderWindow::Draw3D()
{
	Camera.Draw3D();

	axis->Transform = Matrix4x4::CreateTranslation(cursor3D);
	axis->View = View;
	axis->Projection = Projection;
	axis->Draw3D();

	if (Settings::ShowGrid.Value)
	{
		grid->View = View;
		grid->Projection = Projection;
		grid->Draw3D();
	}

	if (_keyboardTest)
	{
	}

	auto drawAllObjects = [this]()
	{
		for(auto& obj : *Objects)
		{
			if(obj.InternalType == ObjectType::IObject3D)
			{
				auto obj_3d = static_cast<IObject3D*>(obj.Object.get());

				auto gizmo = obj_3d->GetGizmo();
				if(gizmo != nullptr)
				{
					gizmo->Selected = obj.Object.get() == this->_selectedObject;
					gizmo->Object = obj.Object.get();
					gizmo->Draw3D();
				}
			}
		}
	};

	//Main rendering pass
	drawAllObjects();	

	//Picking pass
	/*
	if(_requestedPicking)
	{
		this->_picking->Begin();
		drawAllObjects();
		this->_picking->End();

		auto id = this->_picking->Pick(this->_pickingCoords);
		if(id.has_value())
		{
			auto selection = Objects->operator[](id.value());
			_selectedObject = selection;
			this->cursor3D = static_cast<IObject3D*>(selection)->Position;
		}
	}
	*/

	//billboard->View = this->View;
	//billboard->Projection = this->Projection;
	//billboard->Draw3D();
}

void RenderWindow::SelectObject(IObject* obj)
{
	_selectedObject = obj;
}

void RenderWindow::Draw2D()
{
	this->ClearColor = Color(0, 0, 0, 1);

	SpriteBatch->Begin();
	SpriteBatch->DrawString(
		_font.get(),
		std::format("Mouse {} {}", cameraPos.X, cameraPos.Y),
		Point(20, 20),
		1
	);

	//if(_keyboardTest)
	//	SpriteBatch->DrawNormalized(sob.get(), RectangleF(0, 0, 1, 1));
	SpriteBatch->End();

	for(auto& obj : *Objects)
	{
		auto obj2d = static_cast<IObject2D*>(obj.Object.get());

		auto gizmo = obj2d->GetGizmo();
		if(gizmo != nullptr)
		{ 
			gizmo->Selected = obj.Object.get() == this->_selectedObject;
			gizmo->Object = obj.Object.get();
			gizmo->Draw2D();
		}
	}
}

bool RenderWindow::IsFocused() const
{
	return editorWindow == GetForegroundWindow();
}

void RenderWindow::Reset3DCursor()
{
	cursor3D = Vector3::Zero();
	_selectedObject = nullptr;
}

RenderWindow::~RenderWindow()
{
	_3drsp_gizmos.clear();
}