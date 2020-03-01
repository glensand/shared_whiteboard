//------------------------------------------------------------------------------
// BoostTcpServer.h
//
// BoostTcpServer implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 22.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <vector>
#include "network/BoostTcpSession.h"

// TODO:: refactor server, interface and more abstract entities should be added

namespace Net
{
	class BoostTcpSession;

	class WhiteboardServer final
{
public:
	WhiteboardServer(size_t port);
	~WhiteboardServer() = default;

	void	Run();
	
private:
	void	OnWrite();

	void	Accept();

	void	Receive(BoostTcpSession* client, size_t);

	std::vector<Session>			m_sessions;
	boost::asio::io_service			m_service;
	boost::asio::ip::tcp::acceptor	m_acceptor;

	OnActionCallback				m_OnWriteCallback;
	std::string						m_bufStream;

	std::mutex m_receiveLock;
};
	
}

