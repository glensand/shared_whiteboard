/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

	void			DrawShape(const Shape& shape) override;
	
	void			OnMouseHandleInner(int event, int x, int y);
	static void		OnMouseHandle(int event, int x, int y, int, void* instance);

	void			OnKeyboardHandle(int k);
	
private:
	void			Run();
	
	void			Show() const override;
	std::string		m_appName { "whiteboard" };
	
	cv::Mat			m_board;
	cv::Mat			m_boardOnFrame;

	int				m_thickness{ 0 };
};

}
