#include "ObjectCollection.hpp"
#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

ObjectCollection::ObjectCollection(IObject* owner) : _owner(owner)
{
}

void ObjectCollection::Add(IObject* ptr)
{
	if(ptr == nullptr) return;

	ptr->SetParent(_owner);
	_objects.push_back(ptr);
}

void ObjectCollection::Remove(IObject* ptr)
{
	if(ptr == nullptr) return;

	ptr->SetParent(nullptr);

	if (!_objects.empty())
	{
		_objects.erase(std::remove(_objects.begin(), _objects.end(), ptr), _objects.end());
	}
}

void ObjectCollection::Remove(size_t index)
{
	if (index >= _objects.size()) return;

	_objects.at(index)->SetParent(nullptr);
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
	auto detachedList = std::move(_objects);

	for (auto& obj : detachedList)
	{
		if(obj) obj->SetParent(nullptr);
	}
}

std::vector<IObject*> ObjectCollection::Find(std::function<bool(IObject*)> predicate) const noexcept
{
	std::vector<IObject*> r;

	for(const auto& obj : _objects) 
		if(predicate(obj)) r.push_back(obj);

	return r;
}

std::vector<IObject*>::iterator ObjectCollection::begin() noexcept
{
	return _objects.begin();
}

std::vector<IObject*>::const_iterator ObjectCollection::begin() const noexcept
{
	return _objects.begin();
}

std::vector<IObject*>::iterator ObjectCollection::end() noexcept
{
	return _objects.end();
}

std::vector<IObject*>::const_iterator ObjectCollection::end() const noexcept
{
	return _objects.cend();
}