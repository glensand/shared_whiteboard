//------------------------------------------------------------------------------
// SharedWhiteboard.h
//
// SharedWhiteboard implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 21.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include "whiteboard/Whiteboard.h"
#include "network/BoostTcpClient.h"

namespace wboard
{
namespace shared
{
	
class SharedWhiteboard
{
public:

	SharedWhiteboard(WhiteBoard&& wb, const std::string& host, const std::string& port);
	virtual ~SharedWhiteboard() = default;

	void	Run();
	void	Send(const Shape&);
	
	void	Receive(size_t count);
	void	OnSentCallback();
	
private:
	std::function<void(const Shape&)>	m_onDrawCallback;
	WhiteBoard							m_whiteBoard;
	Net::BoostTcpClient					m_tcpClient;

	Net::OnActionCallback				m_OnSentCallback;
	Net::OnActionCallback				m_onReadCallback;

	std::stringstream					m_writeStream;
};

}
}
