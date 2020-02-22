//------------------------------------------------------------------------------
// WhiteBoardBase.h
// 
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include <functional>
#include <boost/signals2.hpp>

#include "render/RenderBase.h"

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

	virtual void		Open() = 0;
	virtual void		Close() = 0;

	void				Draw(const Shape& shape) const;
	void				RegisterOnDrawCallback(const std::function<void(const Shape& shape)>& callback);
	
protected:
	void				Draw() const;
	void				Update();
	
	void				SetRender(Render&& render);
	void				SetShape(ShapeType type);
	
	void				ChangeState();
	
	const RenderCtx&	GetRenderCtx() const;

	template<typename T>
	void AddShape(ShapeType type);

	int				m_x{ 0 };
	int				m_y{ 0 };

	State			m_state{ State::WAIT };
	RenderCtx		m_ctx;

private:
	Render			m_render;
	
	boost::signals2::signal<void(const Shape&)>		m_onDrawSignal;
	std::unordered_map<ShapeType, Shape>			m_shapesBuffer;
};

template <typename T>
void WhiteBoardBase::AddShape(ShapeType type)
{
	auto ptr = std::make_shared<T>(type);

	m_shapesBuffer.emplace(ptr->Type, ptr);
}

using WhiteBoard = std::unique_ptr<WhiteBoardBase>;

}

