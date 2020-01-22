#pragma once
#include <string>
#include <opencv2/core/mat.hpp>

#include "RenderCV.h"

namespace wboard
{
	
class WhiteBoard final
{
public:

	WhiteBoard(const std::string& appName);
	~WhiteBoard();

	void			Open(const std::string& path);

private:
	void			Update();

	static void		OnMouseHandle(int event, int x, int y, int, void* instance);
	void			OnMouseHandleInner(int x, int y);

	static void		OnBlurParamsChanged(int x, void* instance);

	std::string		m_appName;

	int				m_blurRadius;
	int				m_blurStrength;

	int				m_posX;
	int				m_posY;

	cv::Mat			m_whiteboard;
	Conte			m_blurred;
};
	
}

