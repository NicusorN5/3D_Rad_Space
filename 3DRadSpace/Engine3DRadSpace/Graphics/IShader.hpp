#pragma once
#include "ShaderFeatureLevel.hpp"
#include "IGPUResource.hpp"
#include "../Reflection/IReflectedField.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;
	class ISamplerState;

	class E3DRSP_GRAPHICS_EXPORT IShader : IGPUResource
	{
	protected:
		IShader() = default;
	public:
		IShader(const IShader&) = delete;
		IShader(IShader&&) noexcept = default;

		IShader& operator=(const IShader&) = delete;
		IShader& operator=(IShader&&) noexcept = default;

		///<summary>
		/// Sets an entire uniform buffer to the shader.
		/// </summary>
		virtual void SetData(unsigned index, const void *data, unsigned dataSize) = 0;
		virtual void SetTexture(unsigned index, ITexture2D *texture) = 0;
		virtual void SetTextures(std::span<ITexture2D*> textures) = 0;
		virtual void SetSampler(unsigned index, ISamplerState *samplerState) = 0;
		virtual void SetShader() = 0;

		virtual std::vector<Reflection::IReflectedField*> GetVariables() const = 0;
		virtual void Set(const std::string& name, const void* data, unsigned dataSize) = 0;

		template<typename T>
		void Set(const std::string& name, const T& data)
		{
			Set(name, &data, sizeof(T));
		}

		virtual ShaderFeatureLevel GetFeatureLevel() = 0;
		virtual std::string GetEntryName() = 0;
		virtual const char* GetCompilationErrorsAndWarnings() = 0;

		~IShader() override = default;
	};
}