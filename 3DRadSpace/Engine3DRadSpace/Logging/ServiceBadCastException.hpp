#pragma once
#include "Exception.hpp"
#include "../Core/Tag.hpp"

namespace Engine3DRadSpace
{
	namespace Logging
	{
		class E3DRSP_LOGGING_EXPORT ServiceBadCastException : public Exception
		{
		public:
			template<typename T>
			ServiceBadCastException(Tag<T> to) :
				Exception(std::format("Cast to {} failed", typeid(T).name()))
			{
			}

			template<typename T>
			ServiceBadCastException(Tag<T> to, const std::string& details) :
				Exception(std::format("Cast to {} failed: {}", typeid(T).name(), details))
			{
			}
		
			~ServiceBadCastException() override = default;
		};
	}
}