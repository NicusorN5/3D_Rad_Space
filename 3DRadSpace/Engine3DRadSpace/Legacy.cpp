#include "Legacy.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Projects;

static ObjectList *objList;
static std::filesystem::path projectPath;

void Engine3DRadSpace::Legacy::SetObjectList(ObjectList *list)
{
	objList = list;
}

void Engine3DRadSpace::Legacy::SetProjectPath(const std::filesystem::path &path)
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

void iObjectReset(unsigned obj_x)
{
	auto obj = Serializer::LoadObjectFromProject(projectPath, obj_x);
	objList->Replace(obj, obj_x);
}

void iObjectOrientation(unsigned obj_x, Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr)
	{
		q = obj->Rotation;
		return;
	}
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr)
	{
		auto r = obj->Rotation;
		q = Quaternion(r, r, r, r);
		return;
	}
	q = Quaternion();
}

void iObjectOrientationSet(unsigned obj_x, const Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Rotation = q;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Rotation = q.X;
}

void iObjectOrientationReset(unsigned obj_x, Quaternion& q)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		q = refobj_lst->Rotation = temp_obj->Rotation;
	}
}

void iObjectLocation(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Position;
	else v = Vector3();
}

void iObjectLocationSet(unsigned obj_x, const Vector3& v)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Position = v;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Position = Vector2(v.X, v.Y);
}

void DLLEXPORT iObjectLocationReset(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		v = refobj_lst->Position = temp_obj->Position;
	}
}

void iObjectScaleSet(unsigned obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Scale = v;
}

void iObjectScale(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Scale;
	else v = Math::Vector3();
}

float iObjectKmh(unsigned obj_x)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		return obj->LinearVelocity.Length();
	}
	else return 0.0f;
}

void iObjectVelocity(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::LinearVelocity);
		v = obj->LinearVelocity;
	}
	else v = Vector3::Zero();
}

void iObjectVelocitySet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->LinearVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void iObjectSpin(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Read(IPhysicsObject::PhysicsProperty::AngularVelocity);
		v = obj->AngularVelocity;
	}
	else v = Vector3::Zero();
}

void iObjectSpinSet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->AngularVelocity = v;
		obj->Apply(IPhysicsObject::PhysicsProperty::LinearVelocity);
	}
}

void iObjectTorqueApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if (obj != nullptr) obj->ApplyTorque(v);
}

void iObjectAngularAccelerationApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAngularAcceleration(v);
}

void iObjectForceApply(unsigned ojb_x, Math::Vector3 f, Math::Vector3* p)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[ojb_x]);
	if(obj != nullptr)
	{
		if(p != nullptr) obj->ApplyForce(f, *p);
		else obj->ApplyForce(f);
	}
}

void iObjectAccelerationApply(unsigned obj_x, const Math::Vector3& acc)
{
	auto obj = dynamic_cast<IPhysicsObject*>((*objList)[obj_x]);
	if(obj != nullptr) obj->ApplyAcceleration(acc);
}

void iObjectDampingApply(unsigned obj_x, Math::Vector3& v, bool is_rotation, bool local_axis)
{
	
}

int iObjectScan(
	unsigned obj_x, 
	const Math::Vector3& origin,
	const Math::Vector3& direction,
	float radius,
	Math::Vector3& contactPoint, 
	Math::Vector3& contactNormal)
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

void iObjectTextSet(unsigned obj_x, const std::string &str)
{
	auto txtPrint = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if(txtPrint != nullptr) txtPrint->Text = str;
}

void iObjectRefresh(unsigned obj_x, const std::string& path)
{
	auto obj = (*objList)[obj_x];
	obj->Load(path);
}

int iStringLen(const std::string &str)
{
	return str.length();
}

void iStringUCase(const std::string &in, std::string &out)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::tolower(c);
	});
}

void iStringLCase(const std::string& in, std::string& out)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::tolower(c);
	});
}

void iShaderSet(unsigned obj_x, const std::string& path)
{
	auto obj = dynamic_cast<Skinmesh*>((*objList)[obj_x]);
	for (auto& mesh : *obj->GetModel())
	{
		for (auto& meshPart : *mesh)
		{
			//meshPart->SetShaders()
		}
	}
}