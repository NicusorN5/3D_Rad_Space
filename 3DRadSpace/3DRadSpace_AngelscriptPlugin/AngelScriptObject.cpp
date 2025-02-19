#include "AngelScriptObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

using namespace Engine3DRadSpace_Angelscript;

AngelScriptObject::AngelScriptObject(const std::string& name, bool enabled, const std::string& source) :
	IObject(name, enabled)
{
}
