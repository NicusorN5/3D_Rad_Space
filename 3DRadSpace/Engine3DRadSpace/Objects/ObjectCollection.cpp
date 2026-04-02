#include "ObjectCollection.hpp"

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