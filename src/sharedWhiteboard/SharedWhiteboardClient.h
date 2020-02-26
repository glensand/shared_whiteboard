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
#include "network/BoostTcpClient.h"

namespace wboard
{
namespace shared
{
	
class SharedWhiteboardClient
{
public:

	SharedWhiteboardClient(WhiteBoard&& wb, const std::string& host, const std::string& port);
	virtual ~SharedWhiteboardClient() = default;

	void	Run();
	void	Send(const Shape&);
	
	void	Receive(size_t count);
	void	OnSentCallback();
	
private:
	std::function<void(const Shape&)>	m_onDrawCallback;
	WhiteBoard							m_whiteBoard;

	Net::OnActionCallback				m_OnSentCallback;
	Net::OnActionCallback				m_onReadCallback;

	Net::BoostTcpClient					m_tcpClient;
	std::string		m_port;
	std::string		m_host;
	std::string		m_writeBuffer;
};

}
}
