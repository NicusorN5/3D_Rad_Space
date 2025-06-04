#pragma once
#include "../Math\Matrix4x4.hpp"
#include "../Core/IInitializable.hpp"
#include "../Core/IUpdateable.hpp"
#include "../Reflection/UUID.hpp"
#include "../Content/ILoadable.hpp"

namespace Engine3DRadSpace
{
	class Game;

	namespace Objects::Gizmos
	{
		class IGizmo;
	}

	class DLLEXPORT IObject : public IInitiializable, public IUpdateable, public ILoadable
	{
	protected:
		Game* _game = nullptr;
		Graphics::GraphicsDevice* _device = nullptr;
		/// <summary>
		/// Default constructor used for reflection. Objects created with this constructor are initially invalid, until internalInitialize() is called.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="tag"></param>
		/// <param name="enabled"></param>
		/// <param name="visible"></param>
		explicit IObject(const std::string& name = "Empty", bool enabled = false, bool visible = false);
	public:
		std::string Name;
		bool Enabled;
		bool Visible;

		/// <summary>
		/// Called by ObjectsList to set the _game Game instance. If there are objects manually managed, this MUST be called before Initialize or EditorInitialize.
		/// </summary>
		/// <param name="game">Application context</param>
		void InternalInitialize(Game* game);

		virtual Reflection::UUID GetUUID() const noexcept = 0;
		virtual Objects::Gizmos::IGizmo* GetGizmo() const noexcept = 0;

		Graphics::GraphicsDevice *GetGraphicsDeviceHandle();
		Game* GetGame();

		///Getters and setters for events and visual scripting

		virtual void Enable();
		virtual void Disable();
		virtual bool Switch();

		virtual void Show();
		virtual void Hide();
		virtual bool SwitchVisibility();

		virtual ~IObject();

		friend class Game;
		friend class ObjectList;
	};
}


