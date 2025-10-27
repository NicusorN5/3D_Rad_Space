#include "Effect.hpp"

using namespace Engine3DRadSpace::Graphics;

Effect::Effect(IGraphicsDevice *device, IVertexShader *vertexShader, IFragmentShader *fragmentShader, IHullShader *hullShader,
	IDomainShader *domainShader, IGeometryShader *geometryShader ):
	_device(device),
	_vertex(vertexShader),
	_hull(hullShader),
	_domain(domainShader),
	_geometry(geometryShader),
	_pixel(fragmentShader)
{
}

int Effect::SetAll() const noexcept
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetHull()) ++r;
	if(SetDomain()) ++r;
	if(SetGeometry()) ++r;
	if(SetFragment()) ++r;
	return r;
}

int Effect::SetBasic() const noexcept
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetFragment()) ++r;
	return r;
}

bool Effect::SetVertex() const noexcept
{
	if(_vertex == nullptr) return false;

	_device->SetShader(_vertex.get());
	return true;
}

bool Effect::SetHull() const noexcept
{
	if(_hull == nullptr) return false;

	_device->SetShader(_hull.get());
	return true;
}

bool Effect::SetDomain() const noexcept
{
	if(_domain == nullptr) return false;

	_device->SetShader(_domain.get());
	return true;
}

bool Effect::SetGeometry() const noexcept
{
	if(_geometry == nullptr) return false;

	_device->SetShader(_geometry.get());
	return true;
}

bool Effect::SetFragment() const noexcept
{
	if(_pixel == nullptr) return false;

	_device->SetShader(_pixel.get());
	return true;
}

IShader* Effect::GetVertexShader() const noexcept
{
	return _vertex.get();
}

IShader* Effect::GetHullShader() const noexcept
{
	return _hull.get();
}

IShader* Effect::GetDomainShader() const noexcept
{
	return _domain.get();
}

IShader* Effect::GetGeometryShader() const noexcept
{
	return _geometry.get();
}

IShader* Effect::GetPixelShader() const noexcept
{
	return _pixel.get();
}

void Effect::SetTexture(ITexture2D* texture, int idx) noexcept
{
	if (_vertex) _vertex->SetTexture(idx, texture);
	if (_hull) _hull->SetTexture(idx, texture);
	if (_domain) _domain->SetTexture(idx, texture);
	if (_geometry) _geometry->SetTexture(idx, texture);
	if (_pixel) _pixel->SetTexture(idx, texture);
}

void Effect::SetSampler(ISamplerState* sampler, int idx) noexcept
{
	if (_vertex) _vertex->SetSampler(idx, sampler);
	if (_hull) _hull->SetSampler(idx, sampler);
	if (_domain) _domain->SetSampler(idx, sampler);
	if (_geometry) _geometry->SetSampler(idx, sampler);
	if (_pixel) _pixel->SetSampler(idx, sampler);
}