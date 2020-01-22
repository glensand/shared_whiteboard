#include "Whiteboard.h"
#include "ShapeSerializer.h"

namespace wboard
{
	
void WhiteBoardBase::Draw() const
{
	if (m_state == State::WAIT) return;
	m_render->Render(GetRenderCtx());
}

void WhiteBoardBase::Send() const
{
	if (m_state != State::FINISH) return;

//	if(m_isServer)

	auto& shape = m_shapesBuffer.at(m_curShapeHash);
	
	auto pack = ShapeSerializer::Instance().Serialize(shape);
}

void WhiteBoardBase::Recieve()
{
	
}

void WhiteBoardBase::Update()
{
	auto& shape = m_shapesBuffer[m_curShapeHash];
	
	if(m_state == State::WAIT)
	{
		shape->P1 = { m_x, m_y };
		shape->P2 = { m_x, m_y };
	}

	if(m_state == State::FINISH || m_state == State::DRAWING)
		shape->P2 = { m_x, m_y };
	
	m_ctx->Shape = shape;
}

void WhiteBoardBase::ChangeState()
{
	if (m_state == State::WAIT) m_state = State::DRAWING;
	else if (m_state == State::DRAWING) m_state = State::FINISH;
	else m_state = State::WAIT;
}

const RenderCtx& WhiteBoardBase::GetRenderCtx() const
{
	return m_ctx;
}

void WhiteBoardBase::SetRender(Render&& render)
{
	m_render = std::move(render);
}

void WhiteBoardBase::SetShape(ShapeType hash)
{
	m_curShapeHash = hash;
}

void WhiteBoardBase::SetShape(const Shape& hash)
{
	//m_curShapeHash = hash;
}
	
}
