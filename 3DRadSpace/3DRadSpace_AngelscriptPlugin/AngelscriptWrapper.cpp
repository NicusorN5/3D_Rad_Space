#include "AngelscriptWrapper.hpp"

#define AS_USE_NAMESPACE
#include <angelscript.h>
#include "AngelScript_AddOns\scriptstdstring.h"

#include <cassert>
#include <format>

#include <Engine3DRadSpace\3DRadSpace.hpp>
#include <Engine3DRadSpace\Legacy.hpp>

using namespace Engine3DRadSpace_Angelscript;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

using namespace AngelScript;

void AngelScriptWrapper_MessageCallback(const AngelScript::asSMessageInfo* msg, void* param)
{
	if(msg->type == AngelScript::asMSGTYPE_WARNING)
		SetLastWarning(std::format("({}, {}) : Warning {}", msg->section, msg->row, msg->col, msg->message));
	else if(msg->type == AngelScript::asMSGTYPE_INFORMATION)
		SetLastMessage(std::format("({}, {}) : Information {}", msg->section, msg->row, msg->col, msg->message));
	if(msg->type == AngelScript::asMSGTYPE_ERROR)
		SetLastWarning(std::format("({}, {}) : Error {}", msg->section, msg->row, msg->col, msg->message));
}

AngelScriptWrapper::AngelScriptWrapper()
{
	// Create the script engine
	_engine = AngelScript::asCreateScriptEngine();
	if(_engine == nullptr)
		throw Exception("Failed to initialize AngelScript engine!");

	//https://www.angelcode.com/angelscript/sdk/docs/manual/doc_hello_world.html

	auto engine = static_cast<AngelScript::asIScriptEngine*>(_engine);

	int r = engine->SetMessageCallback(asFUNCTION(AngelScriptWrapper_MessageCallback), 0, AngelScript::asCALL_CDECL); assert( r >= 0 );
	RegisterStdString(engine);

#pragma region Vector2
	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	auto v2ctor_def = [](Vector2 * self)
	{
		new (self) Vector2;
	};
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v2ctor_def), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	auto v2ctor = [](float x, float y, Vector2* self)
	{
		new (self) Vector2(x, y);
	};
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(v2ctor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	auto v2ctor_list = [](float *list, Vector2 *self)
	{
		new(self) Vector2(list[0], list[1]);
	};
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_LIST_CONSTRUCT, "void f(int &in) {float, float}", asFUNCTION(v2ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	auto v2ctor_cpy = [](const Vector2& cpy, Vector2* self)
	{
		new (self) Vector2(cpy);
	};
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_LIST_CONSTRUCT, "void f(const Vector2&)}", asFUNCTION(v2ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//destructor
	auto v2dtor = [](Vector2* v)
	{
		v->~Vector2();
	};
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(v2dtor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//fields
	r = engine->RegisterObjectProperty("Vector2", "float X", asOFFSET(Vector2, X)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector2", "float Y", asOFFSET(Vector2, Y)); assert(r >= 0);

	//methods
	r = engine->RegisterObjectMethod("Vector2", "float Length()", asMETHOD(Vector2, Length), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "float Angle()", asMETHOD(Vector2, Angle), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "float Dot(Vector2)", asMETHODPR(Vector2,Dot,(const Vector2&) const,float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "void Normalize()", asMETHOD(Vector2, Normalize), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& RotateBy(const Vector2&)", asMETHOD(Vector2, RotateBy), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& Hadamard(const Vector2&)", asMETHODPR(Vector2, Hadamard, (const Vector2&), Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& Transform(const Matrix3x3&)", asMETHODPR(Vector2, Transform, (const Matrix3x3&), Vector2&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = engine->RegisterObjectMethod("Vector2","Vector2 opNeg()", asMETHODPR(Vector2, operator-,(),Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opAddAssign(const Vector2&)", asMETHOD(Vector2, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opSubAssign(const Vector2&)", asMETHOD(Vector2, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opMulAssign(float)", asMETHOD(Vector2, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opDivAssign(float)", asMETHOD(Vector2, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opDivAssign(float)", asMETHOD(Vector2, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opAdd(const Vector2&)", asMETHOD(Vector2,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opSub(const Vector2&)", asMETHODPR(Vector2,operator-,(const Vector2&) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opMul(float)", asMETHODPR(Vector2,operator*,(float) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opDiv(float)", asMETHOD(Vector2,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Vector3

#pragma endregion

#pragma region Legacy
	//Register legacy functions similar to 3D Rad v7.22:
	r = engine->RegisterGlobalFunction("void iObjectStart(const uint)", asFUNCTION(iObjectStart), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectStart(const uint)", asFUNCTION(iObjectStop), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectSwitch(const uint)", asFUNCTION(iObjectSwitch), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectShow(const uint)", asFUNCTION(iObjectShow), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectHide(const uint)", asFUNCTION(iObjectHide), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectShowHideSwitch(const uint)", asFUNCTION(iObjectShowHideSwitch), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Quaternion iObjectOrientation(const uint)", asFUNCTION(iObjectOrientation), AngelScript::asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectOrientationSet(const uint, Quaternion)", asFUNCTION(iObjectOrientationSet), AngelScript::asCALL_CDECL); assert(r >= 0);
#pragma endregion
}
