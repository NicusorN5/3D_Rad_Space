#pragma once
#include "IReflectedFunction.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// "Reflects" a non-member function.
	/// </summary>
	template<typename R, typename ...Args>
	class ReflectedFunction final : public IReflectedFunction
	{
	public:
		using Fn = R(*)(Args...);
	private:
		Fn _fn; 

		R InvokeImpl(std::span<std::any> args) const
		{
			return [&]<std::size_t... Is>(std::index_sequence<Is...>)
			{
				return _fn(std::any_cast<Args>(args[Is])...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}

		R InvokeImpl(std::span<void*> args) const
		{
			return[&]<std::size_t... Is>(std::index_sequence<Is...>) -> R
			{
				return _fn(*static_cast<Args*>(args[Is])...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}

	public:
		ReflectedFunction(const std::string& name, Fn fn) :
			IReflectedFunction(
				sizeof...(Args),
				{GetFieldRepresentation<Args>()...},
				GetFieldRepresentation<R>(),
				name,
				typeid(Fn).name(),
				typeid(Fn)
			),
			_fn(fn)
		{
		}

		R operator()(Args&&... args)
		{
			return _fn(std::forward<Args>(args)...);
		}

		std::any Invoke(void* self, std::span<std::any> args) const override
		{
			(void)self;

			if constexpr(std::is_void_v<R>)
			{
				InvokeImpl(args);
				return {}; //std::any 
			}
			else return std::make_any<R>(InvokeImpl(args));
		}

		void Invoke(void* outReturn, void* self, std::span<void*> args) const override
		{
			(void)self;

			if constexpr(std::is_void_v<R>)
			{
				return InvokeImpl(args); //return void
			}
			else
			{
				auto r = InvokeImpl(args);

				if constexpr(std::is_pointer_v<R>)
				{
					return outReturn = static_cast<void*>(r);
				}
				else if constexpr(std::is_reference_v<R>)
				{
					return outReturn = static_cast<void*>(&r);
				}
				else
				{
					*(static_cast<R*>(outReturn)) = r;
				}
			}
		}

		void* FunctionPointer() const noexcept
		{
			return static_cast<void*>(_fn);
		}
	};
}