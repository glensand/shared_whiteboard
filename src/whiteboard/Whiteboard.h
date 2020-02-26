//------------------------------------------------------------------------------
// WhiteBoardBase.h
// 
// Copyright (c) 2020 Bezborodov Gleb
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
	WhiteBoardBase();
	virtual ~WhiteBoardBase() = default;

	virtual void		Open() = 0;
	virtual void		Close() = 0;

	virtual void		DrawShape(const Shape& shape) = 0;
	void				RegisterOnDrawCallback(const std::function<void(const Shape& shape)>& callback);
	
protected:
	void				SetUpdateFlag(bool val);
	bool				GetUpdateFlag() const;
	
	virtual void		Show() const = 0;
	
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
	Render			m_render;
	
private:
	bool				m_shouldBeUpdated;
	
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

