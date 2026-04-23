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
	_empty(true),
	_object(nullptr)
{
}

void Event::Bind(IReflectedFunction* fn)
{
	if(fn == nullptr)
	{
		throw std::invalid_argument("Cannot bind a null function.");
	}
	if(_empty)
	{
		_returnType = typeid(void);
		_empty = false;
	}

	_fns.emplace_back(fn);
}

void* Event::GetObj() const noexcept
{
	return _object;
}

void Event::InvokeAllReturnless(std::span<std::span<void*>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		_fns[i++]->Invoke(nullptr, _object, argPack);
	}
}

void Event::InvokeAllReturnless(std::span<std::span<std::any>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		std::ignore = _fns[i++]->Invoke(_object, argPack);
	}
}

void Event::InvokeAllReturnless()
{
	for(auto&& fn : _fns)
	{
		std::ignore = fn->Invoke(_object, std::span<std::any>{});
	}
}

void Event::Unbind(void* fnPtr)
{
	std::erase_if(_fns, 
		[fnPtr](std::unique_ptr<IReflectedFunction> &fn) -> bool
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
	return _iterator.operator*()->Get(nullptr);
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

bool Event::ConstIterator::operator==(const Event::ConstIterator& e) const
{
	return _iterator == e._iterator;
}

bool Event::ConstIterator::operator!=(const Event::ConstIterator& e) const
{
	return _iterator != e._iterator;
}