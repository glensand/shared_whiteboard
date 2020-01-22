#include "Whiteboard.h"
#include "utils.h"

namespace wboard
{
	
void WhiteBoardBase::Draw(const Shape& shape)
{
	m_render->Render(GetRenderCtx());
}

void WhiteBoardBase::Send(const Shape& shape)
{
}

void WhiteBoardBase::SetRender(Render&& render)
{
	m_render = std::move(render);
}
	
}
