#include "AssetRenderer.hpp"
#include <Engine3DRadSpace\Graphics\Model3D.hpp>
#include <Engine3DRadSpace\Math\Matrix4x4.hpp>
#include <Engine3DRadSpace\Graphics\SpriteBatch.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

template<> bool AssetRenderer(IGraphicsDevice *device, const std::string &imagePath, ITexture2D *texture)
{
	if(device && texture)
	{
		//texture->SaveToFile(imagePath);
		//CopyFileA()
		return true;
	}
	else return false;
}

template<> bool AssetRenderer(IGraphicsDevice *device, const std::string &imagePath, Model3D *model)
{
	using std::ranges::views::iota;

	if(device && model)
	{
		//std::shared_ptr<BasicTextured> shader = std::make_shared<BasicTextured>(device);

		auto boundingSphere = model->GetBoundingSphere();
		auto cmd = device->ImmediateContext();

		for (auto&& n : iota(0, 3))
		{
			cmd->Clear(Colors::Gray);
			//model->SetShader(shader);
			model->Draw(
				Matrix4x4() *
				Matrix4x4::CreateLookAtView(
					boundingSphere.Center + ((boundingSphere.Radius + 2) *
						Vector3(
							float(cos(std::numbers::pi / 4)),
							0,
							float(sin(std::numbers::pi / 4))
						)),
					Vector3::Zero(),
					Vector3::UnitY()
				) *
				Matrix4x4::CreatePerspectiveProjection(4.f / 3.f, 65, 0.01f, 500.0f)
			);

			cmd->Present();
		}

		cmd->SaveBackBufferToFile(imagePath);
		return true;
	}
	return false;
}

template<>
bool AssetRenderer(IGraphicsDevice* device, const std::string& imagePath, Font* font)
{
	using std::ranges::views::iota;
	if (device && font)
	{
		SpriteBatch spriteBatch(device);

		for (auto&& n : iota(0, 3))
		{
			spriteBatch.Begin();
			spriteBatch.DrawString(font, "The quick brown fox jumps over the lazy dog", Point(20), 1);
			spriteBatch.End();
		}
		device->ImmediateContext()->SaveBackBufferToFile(imagePath);
	}
	return false;
}
