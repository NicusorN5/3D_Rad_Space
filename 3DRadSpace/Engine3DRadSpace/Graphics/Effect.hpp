#pragma once
#include "IVertexShader.hpp"
#include "IHullShader.hpp"
#include "IDomainShader.hpp"
#include "IGeometryShader.hpp"
#include "IFragmentShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT Effect
	{
	protected:
		GraphicsDevice* _device;
		std::unique_ptr<IVertexShader> _vertex;
		std::unique_ptr<IHullShader> _hull;
		std::unique_ptr<IDomainShader> _domain;
		std::unique_ptr<IGeometryShader> _geometry;
		std::unique_ptr<IFragmentShader> _pixel;
	public:
		Effect(GraphicsDevice *device, IVertexShader* vertexShader, IFragmentShader* fragmentShader, IHullShader* hullShader = nullptr,
			IDomainShader* domainShader = nullptr, IGeometryShader* geometryShader = nullptr);

		Effect(const Effect &p) = delete;
		Effect(Effect&& p) noexcept = default;

		Effect &operator =(const Effect &p) = delete;
		Effect& operator =(Effect&& p) noexcept = default;
		
		int SetAll() const noexcept;
		int SetBasic() const noexcept;
		bool SetVertex() const noexcept;
		bool SetHull() const noexcept;
		bool SetDomain() const noexcept;
		bool SetGeometry() const noexcept;
		bool SetFragment() const noexcept;

		IShader* GetVertexShader() const noexcept;
		IShader* GetHullShader() const noexcept;
		IShader* GetDomainShader() const noexcept;
		IShader* GetGeometryShader() const noexcept;
		IShader* GetPixelShader() const noexcept;

		virtual ~Effect() = default;
	};
}