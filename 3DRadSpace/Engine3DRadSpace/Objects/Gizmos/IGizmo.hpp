#pragma once
#include "../IObject.hpp"
#include "../IDrawable2D.hpp"
#include "../IDrawable3D.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	class E3DRSP_OBJECTS_EXPORT IGizmo: public IUpdateable, public IDrawable3D, public IDrawable2D, public ILoadable
	{
	public:
		/// <summary>
		/// The object that's currently selected.
		/// </summary>
		IObject* Object = nullptr;

		bool Selected = false;

		bool Allow3DRendering = true;
		bool Allow2DRendering = true;
		bool AllowUpdating = false;

		virtual ~IGizmo() = default;
	};
}