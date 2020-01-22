#pragma once

#include "RenderBase.h"
#include "utils.h"

namespace wboard
{

void RenderBase::Render(const Shape& shape)
{
	const auto hash = ComputeHash(shape);

	if (m_renders.count(hash) == 0) return;

	m_renders[hash]->Render(shape, m_ctx);
}

void RenderBase::Initialize(size_t hash, RenderInner&& render)
{
	m_renders[hash] = std::move(render);
}

}

