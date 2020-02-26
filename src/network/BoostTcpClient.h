//------------------------------------------------------------------------------
// BoostTcpClient.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 21.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "ITcpClient.h"
#include "BoostTcpSession.h"

#include <boost/asio.hpp>

#include <memory>
#include <thread>

namespace Net
{
	
class BoostTcpClient final : public ITcpClient
{
	using Service = boost::asio::io_service;
	
public:
	BoostTcpClient();

	virtual ~BoostTcpClient();

	bool	Connect(const std::string& host, const std::string& port) override;
	bool	IsOpen() const override;
	
	void	Close() override;

	void	RunAsyncHandler() override;
	void	StopAsyncHandler() override;

	void	Write(const char* data, size_t count) override;
	void	WriteAsync(const char* data, size_t count, const OnActionCallback& callback) override;
	size_t	WriteSome(const char* data, size_t count) override;

	size_t	Read(std::ostream& stream, size_t count) override;
	size_t	ReadSome(std::ostream&) override;
	void	ReadSomeAsync(std::ostream& stream, const OnActionCallback& callback) override;

	void	AwaitData(const OnActionCallback& callback) override;

	void	Receive(std::ostream& stream, size_t count) const override;
	
private:
	Service			m_service{ };

	BoostTcpSession	m_session;
	std::unique_ptr<std::thread>	m_serviceThread{ };
};
	
}
