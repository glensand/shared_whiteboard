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

	Shape	Shape;
};
	
using RenderCtx = std::unique_ptr<RenderCtxBase>;
	
struct IRenderInner
{
	virtual ~IRenderInner() = default;

	// Сюда надо бы рендер контекст передавать
	virtual void	Render(const RenderCtx& ctx) const = 0;
};
	
using RenderInner = std::unique_ptr<IRenderInner>;
	
class RenderBase
{
public:
	
	RenderBase() = default;
	virtual~RenderBase() = default;

	void			Render(const RenderCtx& ctx);
	
protected:
	virtual void	Show() = 0;
	
	virtual void	RenderImpl(const RenderCtx& ctx) const = 0;

	void			Initialize(size_t hash, RenderInner&& render);
	std::unordered_map<size_t, RenderInner>	m_renders;
};

using Render = std::unique_ptr<RenderBase>;
}

