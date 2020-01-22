#pragma once

#include "RenderBase.h"
#include "utils.h"

namespace wboard
{

void RenderBase::Render(const RenderCtx& ctx)
{
	const auto hash = ComputeHash(ctx->Shape);

	if (m_renders.count(hash) == 0) return;

	m_renders[hash]->Render(ctx);

	Show();
}

void RenderBase::Initialize(size_t hash, RenderInner&& render)
{
	m_renders[hash] = std::move(render);
}

}

