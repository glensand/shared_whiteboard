﻿/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

