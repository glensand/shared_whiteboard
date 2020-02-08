﻿//------------------------------------------------------------------------------
// WhiteBoardCv.h
// Common shape serializers, implements chain
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include "Whiteboard.h"
#include <opencv2/core/mat.hpp>

namespace wboard
{
	
class WhiteBoardCv final : public WhiteBoardBase
{
public:

	WhiteBoardCv();
	WhiteBoardCv(const WhiteBoardCv&) = delete;
	WhiteBoardCv(WhiteBoardCv&&) = delete;
	WhiteBoardCv& operator=(WhiteBoardCv&&) = delete;
	WhiteBoardCv operator=(WhiteBoardCv&) = delete;

	virtual ~WhiteBoardCv() = default;

	void			Open() override;
	void			Close() override;
	void			Show() override;
	
	void			OnMouseHandleInner(int event, int x, int y);
	static void		OnMouseHandle(int event, int x, int y, int, void* instance);

	void			ListenKeyboardInput();
	void			OnKeyboardHandle(int k);
	
private:
	std::string		m_appName { "whiteboard" };
	
	cv::Mat			m_board;
	cv::Mat			m_boardOnFrame;

	int				m_thickness{ 0 };
};

}
