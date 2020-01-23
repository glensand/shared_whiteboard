#include "WhiteBoardCV.h"
#include "RenderCV.h"
#include "ShapeData.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

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

	SetRender(std::make_unique<RenderCV>());

	AddShape<SimpleShape>(ShapeType::Circle);
	AddShape<SimpleShape>(ShapeType::Line);
	SetShape(ShapeType::Circle);
	
	//cv::createButton("Circle", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
	//cv::createButton("Line", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
	//cv::createButton("Rect", OnButtonCircle, this, cv::QT_PUSH_BUTTON, false);
}

void WhiteBoardCV::Open()
{
	Show();
	ListenKeyboardInput();
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

void WhiteBoardCV::ListenKeyboardInput()
{
	for(;;)
	{
		const auto pressedKey = cv::waitKey(0);
		OnKeyboardHandle(pressedKey);
	}
}

void WhiteBoardCV::OnKeyboardHandle(int k)
{
	const char key = static_cast<char>(k);
	switch (key)
	{
	case 'c': SetShape(ShapeType::Circle); break;
	case 'l': SetShape(ShapeType::Line); break;
	case 'r': SetShape(ShapeType::Rect); break;

	default: SetShape(ShapeType::Line);
	}
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
	// и вообще лучше выносить в метод
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
	
}
