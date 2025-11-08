#pragma once
#include "IReflectedFunction.hpp"
#include "Reflection.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_REFLECTION_EXPORT Event
	{
		std::vector<std::unique_ptr<Reflection::IReflectedFunction>> _fns;
		std::type_index _returnType;
		bool _empty;
		void* _object;

		void _reset();

		template<typename R>
		void _setReturnType()
		{
			if(_empty)
			{
				_returnType = typeid(R);
				_empty = false;
			}
			else
			{
				if(_returnType != typeid(R))
				{
					throw std::invalid_argument(std::format("return type is required to be {}, as set by the first binding.", _returnType.name()));
				}
			}
		}
	public:
		Event();

		template<typename R, typename F, typename ...Args>
		Event(F fn) : Event()
		{
			(*this) += fn;
		}

		template<typename R, typename O, typename F, typename ...Args>
		Event(O* object, O::F fn)
		{
			_object = static_cast<void*>(object);
			(*this) += fn;
		}

		Event(const Event&) = delete;
		Event(Event&&) = default;

		Event& operator=(const Event&) = delete;
		Event& operator=(Event&&) = default;

		template<typename R, typename F, typename ...Args>
		Event& operator +=(F fn)
		{
			_setReturnType<R>();
			_fns.emplace_back(
				std::make_unique<Reflection::ReflectedFunction<R, Args...>>(
					std::format("Function {} idx {}", typeid(F).name(), _fns.size()),
					fn
				)
			);

			return *this;
		}

		template<typename R, typename O, typename F, typename ...Args>
		Event& operator+=(O::F fn)
		{
			_setReturnType<R>();
			_fns.emplace_back(
				std::make_unique<Reflection::ReflectedMemberFunction<R, O, Args...>>(
					std::format("Class {} Member function {} idx {}", typeid(O).name(), typeid(F).name(), _fns.size()),
					fn
				)
			);

			return *this;
		}

		template<typename O>
		void SetObject(O* object)
		{
			_object = static_cast<void*>(object);
		}

		template<typename R, typename F, typename ...Args>
		void Bind(F fn)
		{
			(*this).operator+=<R, F, Args...>(fn);
		}

		template<typename R, typename O, typename F, typename ...Args>
		void Bind(O::F fn)
		{
			(*this).operator+=<R, O, F, Args...>(fn);
		}

		template<typename R, typename ...Args>
		R operator()(int index, Args&& ...args)
		{
			auto fn = dynamic_cast<Reflection::ReflectedFunction<R, Args...>*>(_fns[index].get());
			return fn(std::forward<Args>(args)...);
		}

		template<typename R>
		std::vector<R> InvokeAll(std::span<std::any> args)
		{
			std::vector<R> ret;
			for(auto&& fn : _fns)
			{
				ret.emplace_back(std::any_cast<R>(fn->Invoke(_object, args)));
			}
			return ret;
		}

		void InvokeAllReturnless(std::span<std::span<std::any>> allArgs);
		void InvokeAllReturnless(std::span<std::span<void*>> allArgs);

		void Unbind(void* fnPtr);
		void UnbindAll();

		const void* operator[](size_t i) const;

		class ConstIterator
		{
			using internal_iterator = std::vector<std::unique_ptr<Reflection::IReflectedFunction>>::const_iterator;
			internal_iterator _iterator;
		public:

			using iterator_category = std::input_iterator_tag;
			using difference_type = ptrdiff_t;
			using value_type = const void*;
			using pointer = const void*;
			using reference = const void*;

			ConstIterator(internal_iterator it);

			reference operator*();
			pointer operator->();
			ConstIterator& operator++();
			ConstIterator operator++(int);

			friend bool operator== (const ConstIterator& a, const ConstIterator& b);
			friend bool operator!= (const ConstIterator& a, const ConstIterator& b);
		};

		ConstIterator cbegin() const;
		ConstIterator cend() const;

		// could use an other custom operator class that exposes the function pointer only, and not the entire details.
		using Iterator = std::vector<std::unique_ptr<Reflection::IReflectedFunction>>::iterator;

		Iterator begin();
		Iterator end();

		const Reflection::IReflectedFunction* ReflFnAt(size_t index);
	};
}