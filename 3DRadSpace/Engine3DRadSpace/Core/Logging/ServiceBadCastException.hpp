#pragma once
#include <typeinfo>
#include "Exception.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace
{
	namespace Logging
	{
		class E3DRSP_CORE_EXPORT ServiceBadCastException : public Exception
		{
		public:
			template<typename T>
			ServiceBadCastException(Tag<T> to) :
				Exception(std::format("Cast to " + typeid(T).name() + " failed: ")
			{
			}

			template<typename T>
			ServiceBadCastException(Tag<T> to, const std::string& details) :
				Exception(std::format("Cast to " + typeid(T).name()+ " failed: " + details)
			{
			}
		
			~ServiceBadCastException() override = default;
		};
	}
}