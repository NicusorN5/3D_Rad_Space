#pragma once
#include "IGraphicsDevice.hpp"
#include "IShader.hpp"
#include "ShaderType.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a vertex, hull, domain, geometry and fragment shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Effect
	{
	protected:
		IGraphicsDevice* _device;
		std::unique_ptr<IShader> _vertex;
		std::unique_ptr<IShader> _hull;
		std::unique_ptr<IShader> _domain;
		std::unique_ptr<IShader> _geometry;
		std::unique_ptr<IShader> _pixel;
	public:
		Effect(
			IGraphicsDevice* device, 
			IShader* vertexShader,
			IShader* fragmentShader, 
			IShader* hullShader = nullptr,
			IShader* domainShader = nullptr,
			IShader* geometryShader = nullptr
		);

		Effect(const Effect &p) = delete;
		Effect(Effect&& p) noexcept = default;

		Effect &operator =(const Effect &p) = delete;
		Effect& operator =(Effect&& p) noexcept = default;
		
		/// <summary>
		/// Sets all the effects.
		/// </summary>
		/// <returns>Number of effects succesfully set.</returns>
		int SetAll() const noexcept;
		/// <summary>
		/// Sets the vertex and fragment shaders.
		/// </summary>
		/// <returns>Count of shaders applied.</returns>
		int SetBasic() const noexcept;
		/// <summary>
		/// Sets the vertex shader.
		/// </summary>
		/// <returns>True if it was successfully set.</returns>
		bool SetVertex() const noexcept;
		/// <summary>
		/// Sets the hull shader.
		/// </summary>
		/// <returns>True if it was successfully set.</returns>
		bool SetHull() const noexcept;
		/// <summary>
		/// Sets the domain shader.
		/// </summary>
		/// <returns>True if it was successfully set.</returns>
		bool SetDomain() const noexcept;
		/// <summary>
		/// Sets the geometry shader.
		/// </summary>
		/// <returns>True if it was successfully set.</returns>
		bool SetGeometry() const noexcept;
		/// <summary>
		/// Sets the fragment shader.
		/// </summary>
		/// <returns>True if it was successfully set.</returns>
		bool SetFragment() const noexcept;

		/// <summary>
		/// Gets the instance of the vertex shader.
		/// </summary>
		/// <returns>VertexShader instance, nullptr if not assigned.</returns>
		IShader* GetVertexShader() const noexcept;
		/// <summary>
		/// Gets the instance of the hull shader.
		/// </summary>
		/// <returns>HullShader instance, nullptr if not assigned.</returns>
		IShader* GetHullShader() const noexcept;
		/// <summary>
		/// Gets the instance of the domain shader.
		/// </summary>
		/// <returns>DomainShader instance, nullptr if not assigned.</returns>
		IShader* GetDomainShader() const noexcept;
		/// <summary>
		/// Gets the instance of the geometry shader.
		/// </summary>
		/// <returns>GeometryShader instance, nullptr if not assigned.</returns>
		IShader* GetGeometryShader() const noexcept;
		/// <summary>
		/// Gets the instance of the fragment/pixel shader.
		/// </summary>
		/// <returns>FragmentShader instance, nullptr if not assigned.</returns>
		IShader* GetPixelShader() const noexcept;

		template<typename T>
		void Set(const std::string& name, const T& value) noexcept
		{
			if (_vertex) _vertex->Set<T>(name, value);
			if (_hull) _hull->Set<T>(name, value);
			if (_domain) _domain->Set<T>(name, value);
			if (_geometry) _geometry->Set<T>(name, value);
			if (_pixel) _pixel->Set<T>(name, value);
		}

		template<typename T>
		void Set(const std::string& name, const T& value, ShaderType shaderType) noexcept
		{
			switch (shaderType)
			{
			case ShaderType::Vertex:
				if (_vertex) _vertex->Set<T>(name, value);
				break;
			case ShaderType::Hull:
				if (_hull) _hull->Set<T>(name, value);
				break;
			case ShaderType::Domain:
				if (_domain) _domain->Set<T>(name, value);
				break;
			case ShaderType::Geometry:
				if (_geometry) _geometry->Set<T>(name, value);
				break;
			case ShaderType::Fragment:
				if (_pixel) _pixel->Set<T>(name, value);
				break;
			default:
				break;
			}
		}

		void SetTexture(ITexture2D* texture, int idx) noexcept;
		void SetSampler(ISamplerState* sampler, int idx) noexcept;

		~Effect() = default;
	};
}