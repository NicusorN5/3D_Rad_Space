#include "Legacy.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;

static ObjectList *objList;
static std::filesystem::path projectPath;

void SetObjectList(ObjectList *list)
{
	objList = list;
}

void SetProjectPath(const char* path)
{
	projectPath = std::filesystem::path(path);
}

void iObjectStart(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = true;
}

void iObjectStop(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = false;
}

void iObjectSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = !((*objList)[obj_x]->Enabled);
}

void iObjectShow(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = true;
}

void iObjectHide(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = false;
}

void iObjectShowHideSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = !((*objList)[obj_x]->Visible);
}

/* TO-DO: Allowing objects to be resetted would require re-reading the project, then a refactor would be necessary.
void iObjectReset(unsigned obj_x)
{
	
}
*/

void iObjectOrientation(int obj_x, Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) q = obj->Rotation;
	else q = Quaternion();
}

void iObjectOrientationSet(int obj_x, const Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Rotation = q;
}

void iObjectLocation(int obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Position;
	else v = Vector3();
}

void iObjectLocationSet(int obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Position = v;
}

void iObjectScaleSet(int obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Scale = v;
}

void iObjectScale(int obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Scale;
	else v = Math::Vector3();
}

float iObjectKmh(int obj_x)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		return obj->LinearVelocity.Length();
	}
	else return 0.0f;
}

void iObjectVelocity(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		v = obj->LinearVelocity;
	}
	else v = Vector3::Zero();
}

void iObjectVelocitySet(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->LinearVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void iObjectSpin(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::AngularVelocity);
		v = obj->AngularVelocity;
	}
	else v = Vector3::Zero();
}

void iObjectSpinSet(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->AngularVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void iObjectTorqueApply(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr) obj->ApplyTorque(v);
}

void iObjectAngularAccelerationApply(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAngularAcceleration(v);
}

void iObjectForceApply(int ojb_x, Math::Vector3 f, Math::Vector3* p)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[ojb_x]);
	if(obj != nullptr)
	{
		if(p != nullptr) obj->ApplyForce(f, *p);
		else obj->ApplyForce(f);
	}
}

void iObjectAccelerationApply(int obj_x, const Math::Vector3& acc)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAcceleration(acc);
}

void iObjectDampingApply(int obj_x, Math::Vector3& v, bool is_rotation, bool local_axis)
{
	
}

int iObjectScan(int obj_x, const Math::Vector3& origin, const Math::Vector3& direction, float radius, Math::Vector3& contactPoint, Math::Vector3& contactNormal)
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

void iObjectTextSet(int obj_x, const std::string str)
{
	auto txtPrint = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if(txtPrint != nullptr) txtPrint->Text = str;
}

void iObjectRefresh(int obj_x, const std::filesystem::path& path)
{
	auto obj = (*objList)[obj_x];
	obj->Load(path);
}

int iStringLen(const char* str)
{
	return static_cast<int>(std::string(str).length());
}

void iStringUCase(const char* in, char* out)
{
	size_t l = std::string(in).length();
	strcpy_s(out, l , in);
	std::transform(out, out + l, out, [](char c)
	{
		return std::toupper(c);
	});
}

void iStringLCase(const char* in, char* out)
{
	size_t l = std::string(in).length();
	strcpy_s(out, l , in);
	std::transform(out, out + l, out, [](char c)
	{
		return std::tolower(c);
	});	
}

void iShaderSet(int obj_x, const std::string& path)
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