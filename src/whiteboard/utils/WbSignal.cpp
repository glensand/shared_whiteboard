#include "Whiteboard.h"
#include "serializer/ShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
void WhiteBoardBase::Draw() const
{
	if (m_state == State::WAIT) return;
	m_render->Render(GetRenderCtx());
}
//------------------------------------------------------------------------------
void WhiteBoardBase::Update()
{
	auto& shape = m_ctx->Shape;
	
	if(m_state == State::WAIT)
	{
		shape->P1 = { m_x, m_y };
		shape->P2 = { m_x, m_y };
	}

	if(m_state == State::FINISH || m_state == State::DRAWING)
		shape->P2 = { m_x, m_y };
}

void WhiteBoardBase::RegisterOnDrawCallback(const std::function<void(const Shape& shape)>& callback)
{
}

//------------------------------------------------------------------------------
void WhiteBoardBase::ChangeState()
{
	if (m_state == State::WAIT) m_state = State::DRAWING;
	else if (m_state == State::DRAWING) m_state = State::FINISH;
	else m_state = State::WAIT;
}
//------------------------------------------------------------------------------
const RenderCtx& WhiteBoardBase::GetRenderCtx() const
{
	return m_ctx;
}
//------------------------------------------------------------------------------
void WhiteBoardBase::SetRender(Render&& render)
{
	m_render = std::move(render);
}
//------------------------------------------------------------------------------
void WhiteBoardBase::SetShape(ShapeType type)
{
	const auto shape = m_shapesBuffer.find(type);
	if(shape == m_shapesBuffer.end()) return;

	m_ctx->Shape = shape->second;
}
//------------------------------------------------------------------------------
}
