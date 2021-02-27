/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

