#pragma once
#include "IVertexShader.hpp"
#include "IHullShader.hpp"
#include "IDomainShader.hpp"
#include "IGeometryShader.hpp"
#include "IFragmentShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	/// <summary>
	/// Represents a vertex, hull, domain, geometry and fragment shader.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Effect
	{
	protected:
		IGraphicsDevice* _device;
		std::unique_ptr<IVertexShader> _vertex;
		std::unique_ptr<IHullShader> _hull;
		std::unique_ptr<IDomainShader> _domain;
		std::unique_ptr<IGeometryShader> _geometry;
		std::unique_ptr<IFragmentShader> _pixel;
	public:
		Effect(IGraphicsDevice*device, IVertexShader* vertexShader, IFragmentShader* fragmentShader, IHullShader* hullShader = nullptr,
			IDomainShader* domainShader = nullptr, IGeometryShader* geometryShader = nullptr);

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

		virtual ~Effect() = default;
	};
}