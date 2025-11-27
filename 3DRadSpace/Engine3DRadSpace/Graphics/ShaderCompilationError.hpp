#pragma once
#include "../Logging/Exception.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ShaderCompilationError : public Logging::Exception
	{
	public:
		ShaderCompilationError(const std::string &err) :
			Exception(err)
		{
		}
	};
}

