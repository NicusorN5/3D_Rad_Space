#pragma once
#include "IReflectedFunction.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Reflects a member function.
	/// </summary>
	/// <typeparam name="R">Return type.</typeparam>
	/// <typeparam name="O">IObject class type this function is member of</typeparam>
	/// <typeparam name="...Args">Method function arguments</typeparam>
	template<ReflectableType R, ReflectableObject O, ReflectableType ...Args>
	class ReflectedMemberFunction final: public IReflectedFunction
	{
	public:
		using Fn = R(O::*)(Args...);
	private:
		Fn _fn;

		/// <summary>
		/// Invokes the function with type-erased arguments.
		/// </summary>
		/// <param name="ptr">Object ptr.</param>
		/// <param name="args">arguments.</param>
		/// <returns>A value of type R.</returns>
		R InvokeImpl(O* ptr, std::span<std::any> args) const
		{
			return [&]<std::size_t... Is>(std::index_sequence<Is...>)
			{
				//return (ptr::_fn*)(std::any_cast<Args>(args[Is])...);
				return std::invoke(_fn, ptr, std::any_cast<Args>(args[Is])...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}

		R InvokeImpl(O* ptr, std::span<void*> args) const
		{
			return [&]<std::size_t... Is>(std::index_sequence<Is...>) 
			{
				//return (ptr::_fn*)(*std::any_cast<Args*>(args[Is])...);
				return std::invoke(_fn, ptr, *static_cast<Args*>(args[Is])...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}
	public:
		/// <summary>
		/// Constructs a reflected member function with the specified name and pointer.
		/// </summary>
		ReflectedMemberFunction(const std::string& name, Fn fn) :
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

		std::any Invoke(void* self, std::span<std::any> args) const override
		{
			if constexpr(std::is_void_v<R>)
			{
				InvokeImpl(static_cast<O*>(self), args);
				return {}; //std::any 
			}
			else return InvokeImpl(static_cast<O*>(self), args);
		}

		void Invoke(void* ptrOut, void* self, std::span<void*> args) const override
		{
			if constexpr(std::is_void_v<R>)
			{
				return InvokeImpl(static_cast<O*>(self), args); //return void
			}
			else
			{
				auto r = InvokeImpl(static_cast<O*>(self), args);

				if constexpr(std::is_pointer_v<R>)
				{
					return ptrOut = static_cast<void*>(r);
				}
				else if constexpr(std::is_reference_v<R>)
				{
					return ptrOut = static_cast<void*>(&r);
				}
				else
				{
					*(static_cast<R*>(ptrOut)) = r;
				}
			}
		}
	};
}