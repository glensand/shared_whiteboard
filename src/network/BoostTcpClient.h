//------------------------------------------------------------------------------
// BoostTcpClient.h
//
// BoostTcpClient implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 21.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace Net
{

class BoostTcpClient
{
	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::unique_ptr<Socket>;
	using Service = boost::asio::io_service;
	
public:
	BoostTcpClient() = default;
	BoostTcpClient(const std::string& host, const std::string& port)
		: m_host(host)
		, m_port(port)
	{}
	
	virtual ~BoostTcpClient() = default;

	bool	Connect();

	void	WriteAsync(std::istream&, const std::function<void(boost::system::error_code, std::size_t)>& errorCallback) const;

	void	AwaitData(const std::function<void(const boost::system::error_code&, size_t)>& callback);

	void	Receive(std::ostream&) const;
	
private:
	std::string				m_host;
	std::string				m_port;
	
	Service					m_service;
	SocketPtr				m_socket;

	enum {bufferSize = 1000};
	char			m_buffer[bufferSize];
};

}
