#include "ObjectList.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Internal;

Engine3DRadSpace::ObjectList::ObjectList(Game* owner):
	_game(owner)
{
}


void Engine3DRadSpace::ObjectList::_validate(ObjectInstance& instance)
{
	instance.Object->InternalInitialize(_game);
	
	if (_game->WasInitialized())
	{
		instance.Object->Initialize();
	}

	if (_game->WasLoaded())
	{
		instance.Object->Load();
	}
}

void Engine3DRadSpace::ObjectList::_validate(IObject* instance)
{
	if (_game->WasInitialized())
	{
		instance->InternalInitialize(_game);
		instance->Initialize();
	}

	if (_game->WasLoaded())
	{
		instance->Load();
	}
}


unsigned ObjectList::Add(IObject* obj)
{
	obj->InternalInitialize(_game);

	std::unique_ptr<IObject> ptr;
	ptr.reset(obj);

	auto& added_obj = _objects.emplace_back(std::move(ptr));

	_validate(added_obj);

	return unsigned(_objects.size() - 1);
}

IObject* ObjectList::Find(unsigned id) const
{
	return _objects[id].Object.get();
}

IObject* ObjectList::Find(const std::string& name) const noexcept
{
	for (auto& [object, id] : _objects)
	{
		if (object->Name == name) 
			return object.get();
	}
	return nullptr;
}

void ObjectList::Remove(unsigned id)
{
	_objects.erase(_objects.begin() + id, _objects.begin() + id + 1);
}

void ObjectList::Remove(const std::string& name)
{
	std::erase_if(_objects, [name](ObjectInstance& p) -> bool
		{
			return p.Object->Name == name;
		});
}

void ObjectList::Remove(IObject* obj)
{
	std::erase_if(_objects, [obj](ObjectInstance& p) -> bool
		{
			return p.Object.get() == obj;
		});
}

void ObjectList::RemoveIf(std::function<bool(IObject*)> f)
{
	std::erase_if(_objects, [f](ObjectInstance& p) -> bool
		{
			return f(p.Object.get());
		});
}

void ObjectList::Replace(IObject* obj, unsigned id) noexcept
{
	auto context = _objects[id].Object->GetGame();
	_objects[id].Object.reset(obj);

	_objects[id].Object->InternalInitialize(context);

	if(context->WasInitialized())
		_objects[id].Object->Initialize();

	if(context->WasLoaded())
		_objects[id].Object->Load();
}

void ObjectList::Clear() noexcept
{
	_objects.clear();
}

IObject* Engine3DRadSpace::ObjectList::operator[](size_t i) const
{
	return _objects[i].Object.get();
}

size_t Engine3DRadSpace::ObjectList::Count() const noexcept
{
	return _objects.size();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::begin()
{
	return _objects.begin();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::end()
{
	return _objects.end();
}

template<>
ObjectList::ObjectInstance::ObjectInstance(std::unique_ptr<IObject>&& obj) : 
	Object(std::move(obj))
{
	auto ptr = Object.get();

	InternalType = ObjectType::IObject;
	if (dynamic_cast<IObject2D*>(ptr) != nullptr) InternalType = ObjectType::IObject2D;
	else if (dynamic_cast<IObject3D*>(ptr) != nullptr)  InternalType = ObjectType::IObject3D;
}

ObjectList::ObjectInstance::ObjectInstance(IObject* obj)
{
	Object.reset(obj);

	auto ptr = Object.get();

	InternalType = ObjectType::IObject;
	if (dynamic_cast<IObject2D*>(ptr) != nullptr) InternalType = ObjectType::IObject2D;
	else if (dynamic_cast<IObject3D*>(ptr) != nullptr)  InternalType = ObjectType::IObject3D;
}

Objects::Camera* ObjectList::GetRenderingCamera()
{
	return this->_camera;
}
