#include "MeshBatcher.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

MeshBatcher::MeshBatcher(IGraphicsDevice* device) :
	_device(device),
	_beginCalled(false)
{
}

void MeshBatcher::Begin()
{
	_draws.clear();
	_beginCalled = true;
}

void MeshBatcher::Submit(
	IVertexBuffer* vertices,
	IIndexBuffer* indices,
	Effect* material,
	const void* forwardConstants,
	size_t forwardConstantsSize,
	const Math::Matrix4x4& world,
	RenderPassType passType
)
{
	if (!_beginCalled)
		throw std::logic_error("Begin() must be called before Submit().");

	BatchedDraw draw;
	draw.Vertices = vertices;
	draw.Indices = indices;
	draw.Material = material;
	draw.World = world;
	draw.PassType = passType;

	if (forwardConstants != nullptr && forwardConstantsSize > 0)
	{
		const std::byte* bytes = static_cast<const std::byte*>(forwardConstants);
		draw.ForwardConstants.assign(bytes, bytes + forwardConstantsSize);
	}

	_draws.push_back(std::move(draw));
}

void MeshBatcher::Draw(ModelMeshPart* meshPart, RenderPassType passType)
{
	if (meshPart == nullptr) return;

	Submit(
		meshPart->GetVertexBuffer(),
		meshPart->GetIndexBuffer(),
		meshPart->GetShaders(),
		&meshPart->Transform,
		sizeof(Math::Matrix4x4),
		meshPart->Transform,
		passType
	);
}

const std::vector<BatchedDraw>& MeshBatcher::Items() const noexcept
{
	return _draws;
}

void MeshBatcher::End()
{
	_beginCalled = false;
}
