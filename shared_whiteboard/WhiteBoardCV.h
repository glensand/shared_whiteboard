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

	void	Open() override;
	void	Close() override;

private:
	cv::Mat			m_board;
	cv::Mat			m_boardOnFrame;

	RenderCtx		m_ctx;
};

}
