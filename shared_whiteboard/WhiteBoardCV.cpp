#include "WhiteBoardCV.h"
#include "RenderCV.h"
#include "ShapeData.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

namespace
{
constexpr size_t		HEIGHT{ 600 };
constexpr size_t		WIDTH{ 800 };

const cv::Scalar		BACKGROUND_COLOR{ 255, 255, 255 };
}

namespace wboard
{
	
WhiteBoardCV::WhiteBoardCV()
{
	cv::namedWindow(m_appName, cv::WINDOW_AUTOSIZE);
	m_board = cv::Mat(HEIGHT, WIDTH, CV_8UC3, BACKGROUND_COLOR);
	m_boardOnFrame = m_board.clone();

	auto context = std::make_unique<ContextCV>();
	context->Board = m_boardOnFrame;
	m_ctx = std::move(context);
	
	cv::setMouseCallback(m_appName, OnMouseHandle, this);
	//cv::createTrackbar("Thickness: ", m_appName, &m_thickness, 100, OnParamsChanged, this);
	
	SetShape(ShapeType::Line);

	SetRender(std::make_unique<RenderCV>());
	
	AddShape<Line>();
	AddShape<Circle>();
	
	//cv::createButton("Circle", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
	//cv::createButton("Line", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
	//cv::createButton("Rect", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
}

void WhiteBoardCV::Open()
{
	Show();
	cv::waitKey(0);
}

void WhiteBoardCV::Close()
{
	cv::destroyWindow(m_appName);
}

void WhiteBoardCV::Show()
{
	cv::imshow(m_appName, m_boardOnFrame);
}

void WhiteBoardCV::OnMouseHandle(int event, int x, int y, int, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<WhiteBoardCV*>(instance)->OnMouseHandleInner(event, x, y);
}

void WhiteBoardCV::OnMouseHandleInner(int event, int x, int y)
{
	if (m_state == State::FINISH)
		m_state = State::WAIT;
	
	m_x = x;
	m_y = y;

	Update();
	
	if (event == cv::EVENT_LBUTTONDOWN)
		ChangeState();

	// вот это очень плохо и так лучше не делать
	// и вообще лучше выносить в мето
	// юзать что-то типо темплейт метода..
	
	auto cvCtx = static_cast<ContextCV*>(m_ctx.get());

	if(m_state == State::DRAWING)
	{
		m_boardOnFrame = m_board.clone();
		cvCtx->Board = m_boardOnFrame;
	}

	if (m_state == State::FINISH || m_state == State::WAIT)
		cvCtx->Board = m_board;

	Draw();
	Show();
	Send();
}

void WhiteBoardCV::OnButtonInner(ShapeType hash)
{
}

void WhiteBoardCV::OnButtonCircle(int state, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<WhiteBoardCV*>(instance)->OnButtonInner(ShapeType::Circle);
}

void WhiteBoardCV::OnButtonLine(int state, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<WhiteBoardCV*>(instance)->OnButtonInner(ShapeType::Line);
}
	
}
