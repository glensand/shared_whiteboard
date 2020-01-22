#pragma once

#include "ShapeData.h"
#include <unordered_map>

// Это по-сути весь рендеринг...
// Времени нихуа нет, поэтому не делаю интерфейсы, но только базовые класс
// от этого на душе тяжелло, знаешь

namespace wboard
{

struct RenderCtxBase
{
	virtual ~RenderCtxBase() = default;
};
	
using RenderCtx = std::unique_ptr< RenderCtxBase>;
	
struct IRenderInner
{
	virtual ~IRenderInner() = default;

	// Сюда надо бы рендер контекст передавать
	virtual void	Render(const Shape& shape, const RenderCtx& ctx) const = 0;
};
	
using RenderInner = std::unique_ptr<IRenderInner>;
	
class RenderBase
{
public:
	
	RenderBase() = default;
	virtual~RenderBase() = default;

	void			Render(const Shape& shape);
	
protected:
	void			Initialize(size_t hash, RenderInner &&render);
	
	virtual void	RenderImpl(const Shape& shape) const = 0;

	RenderCtx		m_ctx;

	std::unordered_map<size_t, RenderInner>	m_renders;
};

}

