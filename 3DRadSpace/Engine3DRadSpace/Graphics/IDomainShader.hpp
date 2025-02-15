/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/IDomainShader.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a domain shader.
	/// </summary>
	class DLLEXPORT IDomainShader : public IShader
	{
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11DomainShader> _shader;
		const char *_determineTarget();
#endif
		void _createShader();
	protected:
		IDomainShader(GraphicsDevice* device, const char* source, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
		IDomainShader(GraphicsDevice* device, const std::filesystem::path& path, const char* fnEntry, ShaderFeatureLevel fs = ShaderFeatureLevel::DX_V4);
	public:
		IDomainShader(IDomainShader &) = delete;
		IDomainShader(IDomainShader &&) noexcept = delete;
		IDomainShader &operator = (IDomainShader &) = delete;
		IDomainShader &operator = (IDomainShader &&) noexcept = delete;

		void SetTexture(unsigned index, Texture2D *texture) override;
		void SetSampler(unsigned index, SamplerState *samplerState) override;
		void SetShader() override;
		void* GetHandle() const noexcept override;

		~IDomainShader() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

