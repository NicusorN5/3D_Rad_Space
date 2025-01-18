#include "Legacy.hpp"
#include "Physics/IPhysicsObject.hpp"
#include "Game.hpp"
#include "Objects/Skinmesh.hpp"
#include "Objects/TextPrint.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;

static ObjectList *objList;
static std::filesystem::path projectPath;

void Engine3DRadSpace::Legacy::SetObjectList(ObjectList *list)
{
	objList = list;
}

void DLLEXPORT Engine3DRadSpace::Legacy::SetProjectPath(const std::filesystem::path& path)
{
	projectPath = path;
}

void Engine3DRadSpace::Legacy::iObjectStart(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = true;
}

void Engine3DRadSpace::Legacy::iObjectStop(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = false;
}

void Engine3DRadSpace::Legacy::iObjectSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = !((*objList)[obj_x]->Enabled);
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectShow(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = true;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectHide(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = false;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectShowHideSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = !((*objList)[obj_x]->Visible);
}

/* TO-DO: Allowing objects to be resetted would require re-reading the project, then a refactor would be necessary.
void DLLEXPORT Engine3DRadSpace::Legacy::iObjectReset(unsigned obj_x)
{
	
}
*/

void Engine3DRadSpace::Legacy::iObjectOrientation(int obj_x, Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) q = obj->Rotation;
	else q = Quaternion();
}

void Engine3DRadSpace::Legacy::iObjectOrientationSet(int obj_x, const Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Rotation = q;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectLocation(int obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Position;
	else v = Vector3();
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectLocationSet(int obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Position = v;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectScaleSet(int obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Scale = v;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectScale(int obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Scale;
	else v = Math::Vector3();
}

float Engine3DRadSpace::Legacy::iObjectKmh(int obj_x)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		return obj->LinearVelocity.Length();
	}
	else return 0.0f;
}

void Engine3DRadSpace::Legacy::iObjectVelocity(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		v = obj->LinearVelocity;
	}
	else v = Vector3::Zero();
}

void Engine3DRadSpace::Legacy::iObjectVelocitySet(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->LinearVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void Engine3DRadSpace::Legacy::iObjectSpin(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::AngularVelocity);
		v = obj->AngularVelocity;
	}
	else v = Vector3::Zero();
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectSpinSet(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->AngularVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectTorqueApply(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr) obj->ApplyTorque(v);
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectAngularAccelerationApply(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAngularAcceleration(v);
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectForceApply(int ojb_x, Math::Vector3 f, Math::Vector3* p)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[ojb_x]);
	if(obj != nullptr)
	{
		if(p != nullptr) obj->ApplyForce(f, *p);
		else obj->ApplyForce(f);
	}
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectAccelerationApply(int obj_x, const Math::Vector3& acc)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAcceleration(acc);
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectDampingApply(int obj_x, Math::Vector3& v, bool is_rotation, bool local_axis)
{
	
}

int Engine3DRadSpace::Legacy::iObjectScan(int obj_x, const Math::Vector3& origin, const Math::Vector3& direction, float radius, Math::Vector3& contactPoint, Math::Vector3& contactNormal)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto intersection = obj->Intersects(
			Ray{
				.Origin = origin,
				.Direction = direction
			}
		);
		if (intersection.has_value())
		{
			float d = intersection.value();
			if (d > radius) return false;
			else
			{
				contactPoint = origin + (d * direction);
				contactNormal = -direction;
				return true;
			}
		}
		else return false;
	}
	else return false;
}

void Engine3DRadSpace::Legacy::iObjectTextSet(int obj_x, const std::string str)
{
	auto txtPrint = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if(txtPrint != nullptr) txtPrint->Text = str;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectRefresh(int obj_x, const std::filesystem::path& path)
{
	auto obj = (*objList)[obj_x];
	obj->Load(path);
}

int DLLEXPORT Engine3DRadSpace::Legacy::iStringLen(const std::string& str)
{
	return static_cast<int>(str.length());
}

void DLLEXPORT Engine3DRadSpace::Legacy::iStringUCase(const std::string& in, std::string& out)
{
	out = in;
	std::transform(out.begin(), out.end(), out.begin(), [](char c)
	{
		return static_cast<char>(std::toupper(c));
	});
}

void DLLEXPORT Engine3DRadSpace::Legacy::iStringLCase(const std::string& in, std::string& out)
{
	out = in;
	std::transform(out.begin(), out.end(), out.begin(), [](char c)
	{
		return static_cast<char>(std::tolower(c));
	});
}

/*
void DLLEXPORT Engine3DRadSpace::Legacy::iShaderSet(int obj_x, const std::string& path)
{
	auto obj = dynamic_cast<Skinmesh*>((*objList)[obj_x]);
	for (auto& mesh : *obj->GetModel())
	{
		for (auto& meshPart : *mesh)
		{
			meshPart->SetShaders()
		}
	}
}
*/