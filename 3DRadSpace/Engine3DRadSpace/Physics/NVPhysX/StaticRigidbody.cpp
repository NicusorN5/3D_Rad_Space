#include "StaticRigidbody.hpp"
#include "../../Games/Game.hpp"
#include "../../Graphics/Model3D.hpp"
#include "../../Objects/Gizmos.hpp"
#include "PhysicsEngine.hpp"
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include <geometry/PxTriangleMesh.h>
#include <geometry/PxTriangleMeshGeometry.h>
#include <PxPhysicsAPI.h>
#include "../../Content/Assets/ModelAsset.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

void StaticRigidbody::_generateRigidbody()
{
	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(_physics)->GetPhysics());

	_material = std::unique_ptr<void, std::function<void(void*)>>(
		nvPhysics->createMaterial(StaticFriction, DynamicFriction, Restitution),
		[](void *material)
		{
			static_cast<physx::PxMaterial*>(material)->release();
		}
	);

	physx::PxTransform transform;
	transform.p = {_position.X, _position.Y, _position.Z};
	transform.q = {_rotation.X, _rotation.Y, _rotation.Z, _rotation.W};

	std::vector<physx::PxTriangleMesh*> meshes;

	physx::PxTolerancesScale toleranceScale;
	physx::PxCookingParams cookParams(toleranceScale);

	for(auto &mesh : *_model)
	{
		for(auto &part : *mesh.get())
		{
			void* verts;
			size_t structSize = part->VertexBuffer->StructSize();
			size_t numVertices = part->VertexBuffer->NumVertices();

			void* indices;
			part->VertexBuffer->ReadData(&verts);
			
			//create a copy of the position vertices.
			std::unique_ptr<Vector3[]> vertices = std::make_unique<Vector3[]>(numVertices); 
			for(size_t i = 0; i < numVertices; ++i)
			{
				vertices[i] = *reinterpret_cast<Vector3*>((static_cast<std::byte*>(verts) + (structSize * i)));
			}

			part->VertexBuffer->EndRead();
			part->IndexBuffer->ReadData(&indices);

			physx::PxTriangleMeshDesc meshDesc;

			meshDesc.points.count = numVertices;
			meshDesc.points.data = vertices.get();
			meshDesc.points.stride = part->VertexBuffer->StructSize();

			meshDesc.triangles.count = part->IndexBuffer->NumIndices();
			meshDesc.triangles.data = indices;
			meshDesc.triangles.stride = sizeof(unsigned);

#if _DEBUG
			auto b = PxValidateTriangleMesh(cookParams, meshDesc);
			PX_ASSERT(b);
			assert(b);
#endif
			meshes.push_back(
				PxCreateTriangleMesh(
					cookParams,
					meshDesc, 
					nvPhysics->getPhysicsInsertionCallback()
				)
			);

			part->IndexBuffer->EndRead();
		}
	}

	_rigidbody = std::unique_ptr<void, std::function<void(void*)>>(nvPhysics->createRigidStatic(transform),
		[](void* body)
		{
			static_cast<physx::PxRigidStatic*>(body)->release();
		}
	);

	auto rigidbody = static_cast<physx::PxRigidStatic*>(_rigidbody.get());
	auto material = static_cast<physx::PxMaterial*>(_material.get());

	for(auto& mesh : meshes)
	{
		auto meshgeometry = physx::PxTriangleMeshGeometry(
			mesh,
			physx::PxMeshScale(physx::PxVec3(_scale.X, _scale.Y, _scale.Z), physx::PxQuat(physx::PxIdentity))
		);
		auto shape = nvPhysics->createShape(meshgeometry, *material);
		rigidbody->attachShape(*shape);
	}

	auto scene = static_cast<physx::PxScene*>(_physics->GetScene());
	scene->addActor(*rigidbody);
}

float StaticRigidbody::_getMass()
{
	return std::numeric_limits<float>::infinity();
}

void StaticRigidbody::_setMass(float mass)
{
}

float StaticRigidbody::_getLinearDamping()
{
	return _linearDamping;
}

void StaticRigidbody::_setLinearDamping(float linearDamping)
{
	static_cast<physx::PxMaterial*>(_material.get())->setDamping(linearDamping);
	_linearDamping = linearDamping;
}

float StaticRigidbody::_getAngularDamping()
{
	return 0.0;
}

void StaticRigidbody::_setAngularDamping(float angularDamping)
{
}

float StaticRigidbody::_getStaticFriction()
{
	return _staticFriction;
}

void StaticRigidbody::_setStaticFriction(float friction)
{
	static_cast<physx::PxMaterial*>(_material.get())->setStaticFriction(friction);
	_staticFriction = friction;
}

float StaticRigidbody::_getDynamicFriction()
{
	return _dynamicFriction;
}

void StaticRigidbody::_setDynamicFriction(float friction)
{
	static_cast<physx::PxMaterial*>(_material.get())->setDynamicFriction(friction);
	_dynamicFriction = friction;
}

float StaticRigidbody::_getRestitution()
{
	return _restitution;
}

void StaticRigidbody::_setRestitution(float restitution)
{
	static_cast<physx::PxMaterial*>(_material.get())->setRestitution(restitution);
	_restitution = restitution;
}

Math::Vector3 StaticRigidbody::_getLinearVelocity()
{
	return Math::Vector3::Zero();
}

void StaticRigidbody::_setLinearVelocity(const Math::Vector3 & linearVelocity)
{
}

Math::Vector3 StaticRigidbody::_getAngularVelocity()
{
	return Math::Vector3::Zero();
}

void StaticRigidbody::_setAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

Math::Vector3 StaticRigidbody::_getMaxAngularVelocity()
{
	return Math::Vector3::Zero();
}

void StaticRigidbody::_setMaxAngularVelocity(const Math::Vector3 & linearVelocity)
{
}

StaticRigidbody::StaticRigidbody(
	IPhysicsEngine* physics,
	Graphics::Model3D* model,
	const Math::Vector3 scale
) : ICollider(physics)
{
	_generateRigidbody();
}

void StaticRigidbody::Update()
{
	auto rigidbody = static_cast<physx::PxRigidStatic*>(_rigidbody.get());
	auto tr = rigidbody->getGlobalPose();

	_position = Vector3(
		tr.p.x,
		tr.p.y,
		tr.p.z
	);
	
	_rotation = Quaternion(
		tr.q.x,
		tr.q.y,
		tr.q.z,
		tr.q.w
	);
}

bool StaticRigidbody::ApplyForce(const Math::Vector3 &force)
{
	return false;
}

bool StaticRigidbody::ApplyForce(const Math::Vector3 &force, const Math::Vector3 &center)
{
	return false;
}

bool StaticRigidbody::ApplyTorque(const Math::Vector3 &force)
{
	return false;
}

bool StaticRigidbody::ApplyAcceleration(const Math::Vector3 &acc)
{
	return false;
}

bool StaticRigidbody::ApplyAngularAcceleration(const Math::Vector3 &acc)
{
	return false;
}

std::optional<float> StaticRigidbody::Intersects(const Math::Ray &r)
{
	auto scene = static_cast<physx::PxScene*>(_physics->GetScene());
	
	auto origin = physx::PxVec3(r.Origin.X, r.Origin.Y, r.Origin.Z);
	auto dir = physx::PxVec3(r.Direction.X, r.Direction.Y, r.Direction.Z);

	physx::PxRaycastBuffer buffer;

	bool result = scene->raycast(
		origin,
		dir,
		std::numeric_limits<float>::infinity(),
		buffer
	);
	if(!result || !buffer.hasBlock) return std::nullopt;
	
	if(buffer.block.actor != static_cast<physx::PxRigidStatic*>(_rigidbody.get())) return false;
	else return buffer.block.distance;
}

void StaticRigidbody::SetPosition(const Vector3& pos, bool wake)
{
	auto rigidbody = static_cast<physx::PxRigidStatic*>(_rigidbody.get());
	auto tr = rigidbody->getGlobalPose();

	tr.p = physx::PxVec3(pos.X, pos.Y, pos.Z);
	rigidbody->setGlobalPose(physx::PxTransform(tr));
}

void StaticRigidbody::SetRotation(const Math::Quaternion & newQuat, bool wake)
{
	auto rigidbody = static_cast<physx::PxRigidStatic*>(_rigidbody.get());
	auto tr = rigidbody->getGlobalPose();
	
	tr.q = physx::PxQuat(newQuat.X, newQuat.Y, newQuat.Z, newQuat.W);
	rigidbody->setGlobalPose(physx::PxTransform(tr));
}

void StaticRigidbody::SetPositionRotation(const Math::Vector3 & newPos, const Math::Vector3 & newQuat, bool wake)
{
	physx::PxTransform tr;
	tr.p = { _position.X, _position.Y, _position.Z};
	tr.q = {_rotation.X, _rotation.Y, _rotation.Z, _rotation.W};

	static_cast<physx::PxRigidStatic*>(_rigidbody.get())->setGlobalPose(tr);
}