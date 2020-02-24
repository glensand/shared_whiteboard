//------------------------------------------------------------------------------
// BoostTcpServer.h
//
// BoostTcpServer implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 22.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include <boost/asio.hpp>

#include "BoostTcpClient.h"

namespace Net
{
	
class BoostTcpServer final
{
public:
	BoostTcpServer(size_t port);
	~BoostTcpServer() = default;

	void	Run();

private:
	void	OnWrite();

	void	Accept();

	void	Receive(BoostTcpClient& client);

	std::vector<Client>				m_sessions;
	boost::asio::io_service			m_service;
	boost::asio::ip::tcp::acceptor	m_acceptor;

	OnActionCallback				m_OnWriteCallback;
	std::stringstream				m_bufStream;

	std::mutex m_receiveLock;
};
	
}

