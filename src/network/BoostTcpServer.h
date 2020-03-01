//------------------------------------------------------------------------------
// BoostTcpServer.h
//
// BoostTcpServer implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 29.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include "network/ITcpServer.h"
#include "BoostTcpSession.h"
#include <unordered_map>

namespace Net
{
	
class BoostTcpServer : public ITcpServer
{
public:

	explicit BoostTcpServer(const std::string& port);
	virtual ~BoostTcpServer() = default;

	void	AwaitConnections(const ServerOnActionCallback& connectionHandler) override;

	void	AwaitData(int clientId, const OnActionCallback& dataReceiveHandler) override;

	void	Receive(std::ostream& stream, size_t count, int clientId) override;

	void	Send(const void* data, size_t size, int clientId) override;

	void	SendAsync(const void* data, size_t size, int clientId, const OnActionCallback& callback) override;

	void	Send(const void* data, size_t size) override;

	void	SendAsync(const void* data, size_t size, const OnActionCallback& callback) override;

private:
	const Session&	FindSession(size_t id) const;

	size_t	m_sessionCounter{ 0 };
	std::unordered_map<int, Session>	m_sessions;
	boost::asio::io_service				m_service;
	boost::asio::ip::tcp::acceptor		m_acceptor;
};
	
}

