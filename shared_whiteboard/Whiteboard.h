#pragma once

#include <unordered_map>

#include "ShapeData.h"
#include "RenderBase.h"

namespace wboard
{
	
class WhiteBoardBase
{
public:
	WhiteBoardBase() = default;
	virtual ~WhiteBoardBase() = default;

	virtual void	Open() = 0;
	virtual void	Close() = 0;

	void			Draw(const Shape& shape);
	void			Send(const Shape& shape);
	
protected:
	void			SetRender(Render &&render);
	virtual const	RenderCtx& GetRenderCtx() const = 0;

	void			OnCurShapeChanged(size_t shapeHash);
	
private:
	size_t			m_curShapeHash;
	Render			m_render;
	
	std::unordered_map<size_t, Shape>	m_shapesBuffer;
};
	
}

