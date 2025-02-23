#include "Skinmesh.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

Skinmesh::Skinmesh() :
    IObject3D("Skinmesh", "..."),
    _model(nullptr)
{
}

Skinmesh::Skinmesh(
    const std::string &name,
    bool visible,
    RefModel3D model, 
    const Vector3 &pos,
    const Quaternion &rot,
    const Vector3& pivot,
    const Vector3& scale
    ) : IObject3D(name, visible, visible, pos, pivot, rot, scale),
    Model(model),
    _model(nullptr)
{
}

Skinmesh::Skinmesh(
    const std::string &name,
    bool visible,
    const std::filesystem::path &path,
    const Vector3 &pos, 
    const Quaternion &rot,
    const Vector3 &pivot,
    const Vector3& scale
) :
    Skinmesh(name, visible, 0, pos, rot, pivot, scale)
{
    _path = std::make_unique<std::string>(path.string());
}

Model3D* Skinmesh::GetModel()
{
    return _model;
}

void Skinmesh::Initialize()
{
}

void Skinmesh::Load()
{
    if (_path != nullptr)
    {
        _model = _game->Content->Load<Model3D>(*_path);
        _path.reset();
    }
    if (Model)
    {
        _model = static_cast<Model3D*>((*_game->Content)[Model]);
    }
}

void Skinmesh::Load(const std::filesystem::path& path)
{
    _model = _game->Content->Load<Model3D>(path, &Model);
}

void Skinmesh::Update()
{
}

void Skinmesh::EditorInitialize()
{
}

void Skinmesh::EditorLoad()
{
    Load();
}

Reflection::UUID Skinmesh::GetUUID() const noexcept
{
    // {C3A243F6-23E2-437F-AE8A-B8E8C2A6E944}
    return {0xc3a243f6, 0x23e2, 0x437f, { 0xae, 0x8a, 0xb8, 0xe8, 0xc2, 0xa6, 0xe9, 0x44 }};
}

void Skinmesh::Draw3D()
{
    if(Visible && _model)
        _model->Draw(GetModelMartix(), _game->View, _game->Projection);
}

void Skinmesh::EditorDraw3D(bool selected)
{
    if(selected)
    {
        //TODO: Draw highlighted model
    }
    if (_model)
    {
        _model->Draw(GetModelMartix(), _game->View, _game->Projection);
    }
}

void Skinmesh::EditorUpdate()
{
}

std::optional<float> Skinmesh::Intersects(const Ray&r)
{
    for (auto& mesh : *_model)
    {
        for (auto& meshPart : *mesh)
        {
            if(!r.Intersects(meshPart->GetBoundingSphere())) continue;

            auto [vertex, index] = meshPart->CreateStagingBuffers();

            void* vertexData = nullptr;
            size_t numVerts = vertex->ReadData(&vertexData);

            void* indexData = nullptr;
            size_t numIndices = index->ReadData(&indexData);

            for (size_t i = 0; i < numIndices; i += 3)
            {
                auto readVector = [&vertex, &vertexData](size_t index) -> Vector3
                {
                    return *reinterpret_cast<Vector3*>((static_cast<std::byte*>(vertexData)) + (vertex->StructSize() * index));
                };
                //Assuming VS_POSITION3 is the first element.
                Vector3 t1 = readVector(reinterpret_cast<unsigned*>(indexData)[i]);
                Vector3 t2 = readVector(reinterpret_cast<unsigned*>(indexData)[i+1]);
                Vector3 t3 = readVector(reinterpret_cast<unsigned*>(indexData)[i+2]);

                Triangle tri{ t1, t2, t3 };
                
                auto dst = r.Intersects(tri);
                if (dst.has_value()) return dst;
            }

            vertex->EndRead();
            index->EndRead();
        }
    }
    return std::nullopt;
}

REFL_BEGIN(Skinmesh, "Skinmesh", "3D Objects", "3D model")
    REFL_FIELD(Skinmesh, std::string, Name, "Name","Skinmesh","Object's name")
    REFL_FIELD(Skinmesh, bool, Visible, "Visible", true, "Is the object visible?")
    REFL_FIELD(Skinmesh, RefModel3D, Model, "Model", 0, "The skinmesh model")
    REFL_FIELD(Skinmesh, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
    REFL_FIELD(Skinmesh, Quaternion, Rotation, "Rotation", Quaternion(), "Object's rotation")
    REFL_FIELD(Skinmesh, Vector3, RotationCenter, "Rotation Center", Vector3::Zero(), "The rotation pivot")
    REFL_FIELD(Skinmesh, Vector3, Scale, "Scale", Vector3::One(), "The skinmesh scale")
REFL_END