#pragma once
#include "IObject3D.hpp"
#include "IObject2D.hpp"
#include "../Reflection/ReflectedObject.hpp"
#include "../Games/Game.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera;
}

namespace Engine3DRadSpace
{
	template<typename O>
	concept GameObject = Reflection::ReflectableObject<O> || std::is_same_v<IObject, O> || std::is_same_v<IObject2D, O> || std::is_same_v<IObject3D, O>;

	class E3DRSP_OBJECTS_EXPORT ObjectList : public IService
	{
	public:
		struct ObjectInstance
		{
			std::unique_ptr<IObject> Object;

			enum class ObjectType : uint8_t
			{
				None = 0,
				IObject = 1,
				IObject2D,
				IObject3D,
			} InternalType;

			ObjectInstance(IObject* obj);

			ObjectInstance(const ObjectInstance& copy) = delete;
			ObjectInstance(ObjectInstance&&) = default;

			template<GameObject O>
			ObjectInstance(std::unique_ptr<O>&& obj);

			template<GameObject O>
			ObjectInstance(O&& obj);

			template<>
			ObjectInstance(std::unique_ptr<IObject> &&obj);

			ObjectInstance& operator=(const ObjectInstance&) = delete;
			ObjectInstance& operator=(ObjectInstance&&) noexcept = default;
		};
	private:
		std::vector<ObjectInstance> _objects;
		Game* _game;
		Objects::Camera* _camera;

		void _validate(ObjectInstance& instance);
		void _validate(IObject* instance);
	public:
		ObjectList(IGame* owner);
		ObjectList(const ObjectList&) = delete;
		ObjectList(ObjectList&&) noexcept = default;

		ObjectList& operator=(const ObjectList&) = delete;
		ObjectList& operator=(ObjectList&&) noexcept = default;

		template<GameObject O, typename ...Params>
		std::pair<O*, unsigned> AddNew(Params&& ...p);

		template<GameObject O>
		std::pair<O*, unsigned> AddNew(O&& object);

		unsigned Add(IObject* obj);

		IObject* Find(unsigned id) const;
		IObject* Find(const std::string& name) const noexcept;

		/// <summary>
		/// Finds and the i-th object of the type O.
		/// </summary>
		/// <typeparam name="O">Object type.</typeparam>
		/// <param name="i">Index</param>
		/// <returns>Returns the i-th object of the type O.</returns>
		template<GameObject O>
		O* Find(unsigned i = 0) const;

		Objects::Camera* GetRenderingCamera();
		void SetRenderingCamera(Objects::Camera* cam);

		Game* GetGame() const noexcept;

		void Remove(unsigned id);
		void Remove(const std::string& name);
		void Remove(IObject* obj);

		void RemoveIf(std::function<bool(IObject*)> f);

		void Replace(IObject* obj, unsigned id) noexcept;

		void Clear() noexcept;

		IObject* operator[](size_t i) const;
		size_t Count() const noexcept;

		std::vector<ObjectInstance>::iterator begin();
		std::vector<ObjectInstance>::iterator end();

		friend class Objects::Camera;
	};

	template<GameObject O>
	inline ObjectList::ObjectInstance::ObjectInstance(std::unique_ptr<O>&& obj) : Object(std::move(obj))
	{
		InternalType = ObjectType::IObject;
		if constexpr (std::is_base_of_v<IObject2D, O>) InternalType = ObjectType::IObject2D;
		else if constexpr (std::is_base_of_v<IObject3D, O>) InternalType = ObjectType::IObject3D;
	}

	template<GameObject O>
	inline ObjectList::ObjectInstance::ObjectInstance(O&& obj)
	{
		Object.reset(new O(std::move(obj)));

		InternalType = ObjectType::IObject;
		if constexpr (std::is_base_of_v<IObject2D, O>) InternalType = ObjectType::IObject2D;
		else if constexpr (std::is_base_of_v<IObject3D, O>) InternalType = ObjectType::IObject3D;
	}

	template<GameObject O, typename ...Params>
	inline std::pair<O*, unsigned> ObjectList::AddNew(Params&& ...p)
	{
		auto& obj = _objects.emplace_back(std::make_unique<O>(std::forward<Params>(p)...));
		_validate(obj);
		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(_objects.size() - 1));
	}

	template<GameObject O>
	inline std::pair<O*, unsigned> ObjectList::AddNew(O&& object)
	{
		auto index = _objects.size() - 1;
		auto& obj = _objects.emplace_back(std::move(object));
		_validate(obj);
		return std::make_pair(static_cast<O*>(obj.Object.get()), unsigned(index));
	}

	template<GameObject O>
	inline O* ObjectList::Find(unsigned i) const
	{
		unsigned c = 0;
		O* ptr = nullptr;

		for (auto& [type, object] : _objects)
		{
			ptr = dynamic_cast<O*>(object.get());
			if (ptr != nullptr)
			{
				c++;
				if (c == i) return ptr;
			}
		}
		return ptr;
	}
}