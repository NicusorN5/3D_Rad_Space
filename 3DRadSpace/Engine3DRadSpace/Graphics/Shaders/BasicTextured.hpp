#pragma once
#include "../Effect.hpp"
#include "..\..\Math\Matrix4x4.hpp"
#include "../Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	/// <summary>
	/// Represents a trivial 3D effect supporting one albedo texture.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT BasicTextured : public Effect
	{
		class VertexShader : public IVertexShader
		{
		public:
			explicit VertexShader(GraphicsDevice *Device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IFragmentShader
		{
		public:
			explicit PixelShader(GraphicsDevice* Device);
		};

		static inline InputLayoutElement elements[] = {
			InputLayoutElement::Position_Vec3,
			InputLayoutElement::Normal_Vec3,
			InputLayoutElement::Tangent_Vec3,
			InputLayoutElement::Bitangent_Vec3,
			InputLayoutElement::TextureCoordinate2D
		};
	public:
		/// <summary>
		/// Constructs a instance of this effect.
		/// </summary>
		/// <param name="device"></param>
		explicit BasicTextured(GraphicsDevice* device);

		/// <summary>
		/// Sets the MVP transform of the mesh being rendered.
		/// </summary>
		/// <param name="m">Model View Projection transform</param>
		void SetTransform(const Math::Matrix4x4& m);
		/// <summary>
		/// Sets the albedo texture.
		/// </summary>
		/// <param name="texture"></param>
		void SetTexture(Texture2D* texture);
		/// <summary>
		/// Sets the sampler state used to sample the texture.
		/// </summary>
		/// <param name="state">Sampler state pointer.</param>
		void SetSampler(SamplerState* state);
	};
}

