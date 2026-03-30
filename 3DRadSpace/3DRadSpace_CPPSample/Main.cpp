#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Graphics/Rendering/PostProcessEffect.hpp>
#include <Engine3DRadSpace/Graphics/Rendering/LinearPixelFogEffect.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

ShaderDescFile mandelbrotShaderDescFile("MandelbrotEffect.hlsl", "Mandelbrot_PixelShader", ShaderType::Fragment, ShaderFeatureLevel::DX_V5);

class MandelbrotEffect : public PostProcessEffect
{
public:
	MandelbrotEffect(IGraphicsDevice* device) : PostProcessEffect(device, mandelbrotShaderDescFile) 
	{
		Enabled = true;
		NotDepthAware = true;
	}
	~MandelbrotEffect() override = default;
};

class MyGame : public Engine3DRadSpace::Game
{
public:
	MyGame() : Game("MyGame")
	{
	}

	void Load() override
	{
		Game::Load();

		PostProcesses->Add<MandelbrotEffect>();
	}

	~MyGame() override = default;
};

int main()
{
	MyGame game;
	game.Run();
}