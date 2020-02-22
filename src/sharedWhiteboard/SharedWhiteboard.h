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
	
	void	Receive();
	void	OnSentCallback();
	
private:
	std::function<void(const Shape&)>	m_onDrawCallback;
	WhiteBoard							m_whiteBoard;
	Net::BoostTcpClient					m_tcpClient;

	std::function<void(const boost::system::error_code&, size_t)>	m_OnSentCallback;
	std::function<void(const boost::system::error_code&, size_t)>	m_onReadCallback;

	std::stringstream	m_writeStream;
};

}
}
