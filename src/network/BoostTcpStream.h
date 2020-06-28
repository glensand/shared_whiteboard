//------------------------------------------------------------------------------
// TcpStream.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 27.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------

#pragma once

#include "Stream.h"

#include <boost/asio.hpp>

namespace Net
{

class BoostTcpStream final : public Stream
{
	using AsioStream = boost::asio::ip::tcp::iostream;
	
public:
	BoostTcpStream(const std::string& host, const std::string& port);
	BoostTcpStream(BoostTcpStream&) = delete;
	BoostTcpStream(BoostTcpStream&&) = delete;
	BoostTcpStream& operator=(BoostTcpStream&&) = delete;
	BoostTcpStream& operator=(BoostTcpStream&) = delete;
	
	virtual ~BoostTcpStream() = default;

	// Stream implementation
	void			Write(const void* data, size_t count) override;
	
	void			Read(void* data, size_t count) override;

	void			FlushAsync(const OnActionCallback& onFlushCallback) override;
	
	void			Flush() override;

	bool			IsOpen() const override;

	void			Close() override;
protected:
	void			LaunchAsync(const std::function<void()>& func) override;
	
private:
	AsioStream		m_tcpStream;
};
	
}

