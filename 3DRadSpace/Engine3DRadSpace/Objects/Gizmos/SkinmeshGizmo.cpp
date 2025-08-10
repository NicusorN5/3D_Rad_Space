#include "SkinmeshGizmo.hpp"
#include "../../Graphics/RasterizerState.hpp"
#include "../../Graphics/Shaders/ShaderManager.hpp"
#include "../../Graphics/Shaders/MeshHighlight.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Skinmesh>::Gizmo()
{
}

void Gizmo<Skinmesh>::Load()
{
	if(Object == nullptr) return;

	auto skinmesh = static_cast<Skinmesh*>(Object);
	_wasLoaded = skinmesh->GetModel() != nullptr;

	if(_wireframe_RasterizerState == nullptr)
	{
		_wireframe_RasterizerState = std::unique_ptr<void, std::function<void(void*)>>(
			new RasterizerState(RasterizerState::Wireframe(std::move(skinmesh->GetGraphicsDeviceHandle()))),
			[](void* rasterizerState)
			{
				delete static_cast<RasterizerState*>(rasterizerState);
			}
		);
	}

	if(_wasLoaded) return;

	Object->Load();
}

void Gizmo<Skinmesh>::Load(const std::filesystem::path& path)
{
}

void Gizmo<Skinmesh>::Draw3D()
{
	if(Object != nullptr)
	{
		auto skinmesh = static_cast<Skinmesh*>(Object);
		if(skinmesh != nullptr)
		{
			skinmesh->Draw3D();
		}

		if(Selected)
		{
			auto device = skinmesh->GetGraphicsDeviceHandle();		
			auto oldRasterizerState = device->GetRasterizerState();
			auto wireframe = static_cast<RasterizerState*>(_wireframe_RasterizerState.get());

			device->SetRasterizerState(wireframe);

			skinmesh->Draw3D();

			auto game = skinmesh->GetGame();
			auto highlight_effect = ShaderManager::LoadShader<Shaders::MeshHighlight>(game->Device.get());

			highlight_effect->SetColor(Color(1.0f, 0.5f, 0.0f, 0.5f));

			game->Device->UnbindDepthBuffer();

			skinmesh->GetModel()->DrawEffect(
				static_cast<Shaders::Effect*>(highlight_effect.get()),
				skinmesh->GetModelMartix() * game->View * game->Projection
			);

			game->Device->SetRenderTargetAndDepth(nullptr, nullptr);
			device->SetRasterizerState(&oldRasterizerState);
		}
	}
}

void Gizmo<Skinmesh>::Draw2D()
{

}

void Gizmo<Skinmesh>::Update()
{

}