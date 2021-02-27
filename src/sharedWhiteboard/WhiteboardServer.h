/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

