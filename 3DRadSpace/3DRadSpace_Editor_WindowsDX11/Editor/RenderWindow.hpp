#pragma once
#include "Engine3DRadSpace/Game.hpp"
#include "Engine3DRadSpace/Graphics/VertexBuffer.hpp"
#include <Engine3DRadSpace/Graphics/Shaders/BlankShader.hpp>
#include <Engine3DRadSpace\Math\Matrix4x4.hpp>
#include <Engine3DRadSpace/Math/Vector2.hpp>
#include <Engine3DRadSpace/Objects/Camera.hpp>
#include <Engine3DRadSpace/Graphics/Model3D.hpp>
#include <Engine3DRadSpace/Graphics/Shaders/BasicTextured.hpp>
#include <Engine3DRadSpace/Graphics/SpriteBatch.hpp>
#include <Engine3DRadSpace/Graphics/Primitives/LineList.hpp>
#include <Engine3DRadSpace/Graphics/Font.hpp>
#include <Engine3DRadSpace/Algorithms/Picking/PickingRenderTargetRender.hpp>

//Despite using namespaces are ill-advised to be used in headers, this header is not meant to be included in other files.
using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Algorithms;
using namespace Engine3DRadSpace::Algorithms::Picking;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

class RenderWindow : public Engine3DRadSpace::Game
{
	Vector2 cameraPos = Vector2(
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(-std::numbers::pi_v<float> / 6)
	);

	Vector3 cursor3D = Vector3::Zero();

	HWND editorWindow;
	Camera Camera;
	std::unique_ptr<LineList> axis;
	std::unique_ptr<LineList> grid;

	float zoom = 5.0f;
	float timer = 0;

	std::unique_ptr<BasicTextured> texturedShader;
	std::unique_ptr<SamplerState> samplerState;

	std::unique_ptr<PickingShader> _pickingShader;

	bool _keyboardTest = false;

	std::unique_ptr<Font> _font;
public:
	RenderWindow(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw2D() override;

	void Draw3D() override;

	bool IsFocused() const;
	void Reset3DCursor();

	~RenderWindow();
};