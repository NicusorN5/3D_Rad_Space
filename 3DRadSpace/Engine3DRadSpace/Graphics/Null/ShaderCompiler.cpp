#include "ShaderCompiler.hpp"
#include "NullShader.hpp"
#include "../EffectManager.hpp"
#include "GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

ShaderCompiler::ShaderCompiler(GraphicsDevice* device)
{
	auto nullShader = _manager->Add("null", std::make_unique<NullShader>());
	
	std::array<IShader*, 1> nullShaderSpan = { nullShader };
	Effect nullEffect(device, nullShaderSpan);

	_manager->Add("null", std::make_unique<Effect>(std::move(nullEffect)));
}

ShaderCompiler::CompileOutput ShaderCompiler::Compile(const ShaderDesc* desc)
{
	(void)desc;

	return std::make_pair<IShader*, ShaderCompilationResult>(
		_manager->GetShader("null"),
		{}
	);
}
ShaderCompiler::EffectCompileOutput ShaderCompiler::CompileEffect(std::span<ShaderDesc*> descs)
{
	(void)descs;

	return std::make_pair<Effect*, ShaderCompilationResult>(
		_manager->GetEffect("null"),
		{}
	);
}