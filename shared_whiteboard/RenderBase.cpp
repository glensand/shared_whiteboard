#pragma once

#include "RenderBase.h"

namespace wboard
{

void RenderBase::Render(const RenderCtx& ctx)
{
	m_renders[ctx->Shape->Type]->Render(ctx);
}

void RenderBase::Initialize(ShapeType hash, RenderInner&& render)
{
	m_renders[hash] = std::move(render);
}

}

