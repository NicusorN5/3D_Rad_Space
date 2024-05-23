#pragma once
#include "../../Libs.hpp"

namespace Engine3DRadSpace
{
	class IObject;
	namespace Reflection
	{
		class ReflectedObject;

		namespace Content
		{
			class ContentManager;
		}

		namespace Editor
		{
			/// <summary>
			/// If a object is found to have this object as a field, a custom UI is going to be used to edit/create the object. Used for Script/Shader objects.
			/// </summary>
			class CustomEditorGUI
			{
			protected:
				CustomEditorGUI() = default;
			public:
				/// <summary>
				/// When called, a platform specific interface is being shown.
				/// </summary>
				/// <param name="data">Reflection data. Exposed fields.</param>
				/// <param name="contentManager">Content manager used to load assets.</param>
				/// <param name="objectBeingEdited">Object being modified by the interface. If null, a new object will be constructed.</param>
				/// <returns>A modified object is being returned. Preferably "objectBeingEdited", if not null.</returns>
				virtual IObject* ShowInterface(ReflectedObject* data, Content::ContentManager* contentManager, IObject* objectBeingEdited = nullptr) = 0;

				CustomEditorGUI(const CustomEditorGUI&) = delete;
				CustomEditorGUI(CustomEditorGUI&&) noexcept = default;

				virtual ~CustomEditorGUI() = default;
			};
		}
	}
}