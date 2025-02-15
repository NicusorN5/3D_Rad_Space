/// ------------------------------------------------------------------------------------------------
/// File:   Reflection/ReflectedFunction.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "FieldRepresentation.hpp"
#include "ReflectedObject.hpp"

namespace Engine3DRadSpace::Reflection
{
	class DLLEXPORT IReflectedFunction
	{
	public:
		virtual unsigned int NumParameters() = 0;
		virtual std::vector<FieldRepresentation> ParametersInfo() = 0;
		virtual FieldRepresentation ReturnedTypeInfo() = 0;
		virtual const char *Name() = 0;

		virtual ~IReflectedFunction() = default;
	};

	template<ReflectableObject O, ReflectableType R, ReflectableType ...Args>
	class ReflectedFunction : public IReflectedFunction
	{
		const char* _name;
		const unsigned _numParams;

		using TypeFn = R(O::*)(Args...);
		void* _function;
	public:
		ReflectedFunction(const char* name, void* fPtr, FieldRepresentation returnType, Args&& ...args):
			_name(name),
			_numParams(sizeof...(Args)),
			_returnType(returnType),
			_paramsType(std::forward<Args>(args)...),
			_function(fPtr)
		{
		}
	};
}