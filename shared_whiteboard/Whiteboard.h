#pragma once

#include <unordered_map>

#include "ShapeData.h"
#include "RenderBase.h"

enum class State
{
	WAIT,
	DRAWING,
	FINISH
};

namespace wboard
{
	
class WhiteBoardBase
{
public:
	WhiteBoardBase() = default;
	virtual ~WhiteBoardBase() = default;

	
	virtual void	Open() = 0;
	virtual void	Close() = 0;
	virtual void	Show() = 0;
	
	void			Draw() const;
	void			Send() const;
	void			Update();

protected:
	void			SetRender(Render&& render);
	void			SetShape(ShapeType hash);

	template<typename T>
	void			AddShape();
	
	void			ChangeState();
	
	const RenderCtx&	GetRenderCtx() const;

	int				m_x{ 0 };
	int				m_y{ 0 };

	State			m_state{ State::WAIT };
	RenderCtx		m_ctx;
private:
	Render			m_render;
	ShapeType		m_curShapeHash;

	std::vector<Shape>					m_shapes;
	std::unordered_map<ShapeType, Shape>	m_shapesBuffer;
};

template <typename T>
void WhiteBoardBase::AddShape()
{
	auto ptr = std::make_shared<T>();

	m_shapesBuffer.emplace(ptr->Type, ptr);
}
}

