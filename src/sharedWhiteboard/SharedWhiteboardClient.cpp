#include "Configure.h"

#include "SharedWhiteboardClient.h"

#include "whiteboard/WhiteBoardCV.h"
#include "sharedWhiteboard/Protocol/ArgumentShape.h"

#include <sstream>
#include <iostream>

namespace wboard
{
//------------------------------------------------------------------------------
SharedWhiteboardClient::SharedWhiteboardClient(WhiteBoard&& wb, Net::StreamPtr&& stream)
	: m_whiteBoard(std::move(wb))
	, m_stream(std::move(stream))
{
	m_onDrawCallback = [this](const Shape& shape)
	{
		Send(shape);
	};
}
//------------------------------------------------------------------------------
SharedWhiteboardClient::~SharedWhiteboardClient()
{
	m_stream->Close();
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::Run()
{	
	RunStreamListening();
	m_whiteBoard->RegisterOnDrawCallback(m_onDrawCallback);
	m_whiteBoard->Open();
	
	m_whiteBoard->Close();
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::Send(const Shape& shape)
{
	m_stream->WriteAsync(ArgumentShape(shape, "NewShape"), [=]()
		{
			m_stream->Flush();
			if constexpr (DEBUG_PRINT)
			{
				std::cout << "SharedWhiteboard::Send()" << std::endl;
			}
		});
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::RunStreamListening()
{
	m_listenerThread = std::thread([this]()
		{
		for(;;)
		{
			const auto argument = m_stream->Read<ArgumentShape>();
			m_whiteBoard->DrawShape(argument.RowValue().Shape);
			if constexpr (DEBUG_PRINT)
			{
				std::cout << "SharedWhiteboardClient::RunStreamListening() render shape" << std::endl;
			}
		}
		});
}
//------------------------------------------------------------------------------	
}

