//------------------------------------------------------------------------------
// BoostTcpSession.h
//
// BoostTcpSession implements...
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

using OnActionCallback = std::function<void(const boost::system::error_code&, size_t)>;

class BoostTcpSession final
{
	using Socket = boost::asio::ip::tcp::socket;
	using Service = boost::asio::io_service;

public:
	BoostTcpSession(Service& service);

	~BoostTcpSession() = default;

	void	WriteAsync(const char* data, size_t count, const OnActionCallback& errorCallback);

	void	AwaitData(const OnActionCallback& callback);

	void	Receive(std::ostream&) const;

	Socket& GetSocket();

	void	SetInitialized(bool init);
	bool	IsInitialized() const;

private:
	Socket	m_socket;
	bool	m_isInitialized;

	enum { bufferSize = 1000 };
	char	m_buffer[bufferSize];
};

using Session = std::unique_ptr<BoostTcpSession>;

}
