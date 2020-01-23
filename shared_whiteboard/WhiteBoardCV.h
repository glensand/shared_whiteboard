#pragma once

#include "Whiteboard.h"
#include <opencv2/core/mat.hpp>

namespace wboard
{
	
class WhiteBoardCV : public WhiteBoardBase
{
public:

	WhiteBoardCV();
	virtual ~WhiteBoardCV() = default;

	void				Open() override;
	void				Close() override;
	void				Show() override;
	
	void				OnMouseHandleInner(int event, int x, int y);
	static void			OnMouseHandle(int event, int x, int y, int, void* instance);

	void				ListenKeyboardInput();
	void				OnKeyboardHandle(int k);
	
private:
	std::string		m_appName { "whiteboard" };
	
	cv::Mat			m_board;
	cv::Mat			m_boardOnFrame;

	int				m_thickness{ 0 };
};

}
