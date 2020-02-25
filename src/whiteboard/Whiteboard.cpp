#include "Whiteboard.h"
#include <iostream>

namespace wboard
{
//------------------------------------------------------------------------------
void WhiteBoardBase::Draw() const
{
	if (m_state == State::WAIT) return;
	m_render->Render(GetRenderCtx());
	
	if(m_state == State::FINISH) 
		m_onDrawSignal(GetRenderCtx()->Shape);
}
//------------------------------------------------------------------------------
void WhiteBoardBase::Draw(const Shape& shape) const
{
	std::cout << "WhiteBoardBase::Draw(const Shape& shape)" << std::endl;

	const auto prev = GetRenderCtx()->Shape;
	GetRenderCtx()->Shape = shape;
	m_render->Render(GetRenderCtx());
	GetRenderCtx()->Shape = prev;
}
//------------------------------------------------------------------------------
void WhiteBoardBase::RegisterOnDrawCallback(const std::function<void(const Shape & shape)>& callback)
{
	m_onDrawSignal.connect(callback);
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
