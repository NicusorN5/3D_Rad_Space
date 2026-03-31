#include "ObjectCollection.hpp"
#include "ObjectCollection.h"
#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

void ObjectCollection::Add(IObject* ptr)
{
	_objects.push_back(ptr);
}

void ObjectCollection::Remove(IObject* ptr)
{
	_objects.erase(std::remove(_objects.begin(), _objects.end(), ptr), _objects.end());
}

void ObjectCollection::Remove(size_t index)
{
	if (index >= _objects.size()) return;
	_objects.erase(_objects.begin() + index);
}

IObject* ObjectCollection::operator[](size_t index) const
{
	if(index > _objects.size()) return nullptr;
	return _objects.at(index);
}

IObject*& ObjectCollection::operator[](size_t index)
{
	return _objects.at(index);
}

size_t ObjectCollection::Count() const noexcept
{
	return _objects.size();
}

void ObjectCollection::Clear()
{
	_objects.clear();
}

ObjectCollection ObjectCollection::Find(std::function<bool(IObject*)> predicate)
{
	ObjectCollection r;

	for(auto& obj : _objects) 
		if(predicate(obj)) r.Add(obj);

	return r;
}

E3DRSP_ObjectCollection E3DRSP_ObjectCollection_Create()
{
	return new ObjectCollection();
}

void E3DRSP_ObjectCollection_Add(E3DRSP_ObjectCollection collection, E3DRSP_IObject object)
{
	static_cast<ObjectCollection*>(collection)->Add(static_cast<IObject*>(object));
}

void E3DRSP_ObjectCollection_Remove(E3DRSP_ObjectCollection collection, E3DRSP_IObject* object)
{
	static_cast<ObjectCollection*>(collection)->Remove(static_cast<IObject*>(*object));
}
void E3DRSP_ObjectCollection_RemoveID(E3DRSP_ObjectCollection collection, size_t index)
{
	static_cast<ObjectCollection*>(collection)->Remove(index);
}
E3DRSP_IObject E3DRSP_ObjectCollection_At(E3DRSP_ObjectCollection collection, size_t index)
{
	return static_cast<E3DRSP_IObject>(static_cast<ObjectCollection*>(collection)->operator[](index));
}

size_t E3DRSP_ObjectCollection_Count(E3DRSP_ObjectCollection collection)
{
	return static_cast<ObjectCollection*>(collection)->Count();
}

void E3DRSP_ObjectCollection_Clear(E3DRSP_ObjectCollection collection)
{
	static_cast<ObjectCollection*>(collection)->Clear();
}