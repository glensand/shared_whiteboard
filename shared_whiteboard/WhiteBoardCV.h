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
	void				OnButtonInner(ShapeType hash);
	
	static void			OnMouseHandle(int event, int x, int y, int, void* instance);
	static void			OnButtonCircle(int state, void* instance);
	static void			OnButtonLine(int state, void* instance);
	
private:
	std::string		m_appName { "whiteboard" };
	
	cv::Mat			m_board;
	cv::Mat			m_boardOnFrame;

	int				m_thickness{ 0 };
};

}
