#include "RenderBase.h"

namespace wboard
{
//------------------------------------------------------------------------------
void RenderBase::Render(const RenderCtx& ctx)
{
	m_renders[ctx->Shape->Type]->Render(ctx);
}
//------------------------------------------------------------------------------
void RenderBase::Initialize(ShapeType type, RenderInner&& render)
{
	m_renders[type] = std::move(render);
}
//------------------------------------------------------------------------------
}

