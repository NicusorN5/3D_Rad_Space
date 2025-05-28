#pragma once
#include "IGizmo.hpp"
#include "../../Reflection/ReflectedObject.hpp" 
#include "../../IObject2D.hpp"
#include "../../IObject3D.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	/// <summary>
	/// Default gizmo. Draws the object without any aiding/debugging/selection effects.
	/// </summary>
	/// <typeparam name="O">IObject</typeparam>
	template<Reflection::ReflectableObject O>
	class Gizmo : public IGizmo
	{
	public:
		Gizmo()
		{
		}

		void Draw3D() override
		{
			if(Object != nullptr)
			{
				auto obj = dynamic_cast<IObject3D*>(Object);
				if(obj != nullptr)
				{
					obj->Draw3D();
				}
			}
		}

		void Draw2D() override
		{
			if(Object != nullptr)
			{
				auto obj = dynamic_cast<IObject2D*>(Object);
				if(obj != nullptr)
				{
					obj->Draw2D();
				}
			}
		}

		void Load() override
		{
			if(Object != nullptr)
			{
				Object->Load();
			}
		}

		void Load(const std::filesystem::path& path) override
		{
			if(Object != nullptr)
			{
				Object->Load(path);
			}
		}

		void Update() override
		{
		}

		~Gizmo() = default;
	};
}