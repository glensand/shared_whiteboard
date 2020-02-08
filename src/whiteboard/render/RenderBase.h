//------------------------------------------------------------------------------
// RenderBase.h
// 
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include "ShapeData.h"
#include <unordered_map>

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
	void			Initialize(ShapeType type, RenderInner&& render);

	std::unordered_map<ShapeType, RenderInner>	m_renders;
};

using Render = std::unique_ptr<RenderBase>;
}

