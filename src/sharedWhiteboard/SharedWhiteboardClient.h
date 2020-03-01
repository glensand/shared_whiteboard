//------------------------------------------------------------------------------
// SharedWhiteboard.h
//
// SharedWhiteboard implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 21.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "whiteboard/Whiteboard.h"
#include "network/Stream.h"
#include <thread>

namespace wboard
{

class SharedWhiteboardClient
{
public:

	SharedWhiteboardClient(WhiteBoard&& wb, Net::StreamPtr&& stream);
	virtual ~SharedWhiteboardClient() = default;

	void	Run();
	
private:
	void	Send(const Shape&);
	void	RunStreamListening();

	std::thread							m_listenerThread;
	std::function<void(const Shape&)>	m_onDrawCallback;
	WhiteBoard							m_whiteBoard;

	Net::StreamPtr						m_stream;
};

}
