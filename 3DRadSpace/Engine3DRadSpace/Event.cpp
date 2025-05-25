#include "Event.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

void Event::_reset()
{
	_empty = true;
	_returnType = typeid(void);
}

Event::Event() :
	_returnType(typeid(void)),
	_empty(true)
{
}

void Event::InvokeAllReturnless(std::span<std::span<void*>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		_fns[i++]->Invoke(nullptr, nullptr, argPack);
	}
}

void Event::InvokeAllReturnless(std::span<std::span<std::any>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		_fns[i++]->Invoke(nullptr, argPack);
	}
}

void Event::Unbind(void* fnPtr)
{
	std::remove_if(_fns.begin(), _fns.end(), 
		[fnPtr](IReflectedFunction* fn) -> bool
		{
			return fn->Get(nullptr) == fnPtr;
		}
	);

	if(_fns.empty())
	{
		_reset();
	}
}

void Event::UnbindAll()
{
	_fns.clear();
	_reset();
}

const void* Event::operator[](size_t i) const 
{
	return _fns.at(i).get()->Get(nullptr);
}

Event::ConstIterator Event::cbegin() const
{
	return ConstIterator(_fns.cbegin());
}

Event::ConstIterator Event::cend() const
{
	return ConstIterator(_fns.end());
}

const IReflectedFunction* Event::ReflFnAt(size_t index)
{
	return _fns[index].get();
}

Event::ConstIterator::ConstIterator(internal_iterator it) : _iterator(it)
{
}

Event::ConstIterator::reference Event::ConstIterator::operator*()
{
	return _iterator.operator*()->Get(nullptr));
}

Event::ConstIterator::pointer Event::ConstIterator::operator->()
{
	return _iterator.operator->()->get()->Get(nullptr);
}

Event::ConstIterator& Event::ConstIterator::operator++()
{
	_iterator++;
	return *this;
}

Event::ConstIterator Event::ConstIterator::operator++(int)
{
	ConstIterator tmp = *this;
	++(*this);
	return tmp;
}

Event::Iterator Event::begin()
{
	return _fns.begin();
}

Event::Iterator Event::end()
{
	return _fns.end();
}

bool Engine3DRadSpace::operator==(const Event::ConstIterator& a, const Event::ConstIterator& b)
{
	return a._iterator == b._iterator;
}

bool Engine3DRadSpace::operator!=(const Event::ConstIterator& a, const Event::ConstIterator& b)
{
	return a._iterator != b._iterator;
}