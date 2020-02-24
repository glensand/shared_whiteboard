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
#include <thread>

namespace Net
{

using OnActionCallback = std::function<void(const boost::system::error_code&, size_t)>;
	
class BoostTcpClient final
{
	using Socket = boost::asio::ip::tcp::socket;
	using SocketPtr = std::unique_ptr<Socket>;
	using Service = boost::asio::io_service;
	
public:
	BoostTcpClient() = default;
	BoostTcpClient(const std::string& host, const std::string& port);

	~BoostTcpClient() = default;

	bool	Connect();

			// <<thread>>
	void	RunService();
	
	void	WriteAsync(const char* data, size_t count, const OnActionCallback& errorCallback) const;

	void	AwaitData(const OnActionCallback& callback);

	void	Receive(std::ostream&) const;

	Socket& GetSocket() const;

	void	SetInitialized(bool init);
	bool	IsInitialized() const;
	
private:
	bool			m_isInitialized;

	std::thread		m_serviceThread;
	
	std::string		m_host;
	std::string		m_port;
	
	Service			m_service;
	SocketPtr		m_socket;
	
	enum {bufferSize = 1000};
	char			m_buffer[bufferSize];
};

using Client = std::unique_ptr<BoostTcpClient>;
	
}
