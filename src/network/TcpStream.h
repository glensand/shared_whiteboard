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
#include "IStreamProvider.h"

#include "ITcpClient.h"
#include <boost/asio.hpp>

namespace Net
{

class TcpStream final : public Stream, public IStreamProvider
{
	using AsioStream = boost::asio::ip::tcp::iostream;
	
public:
	TcpStream(const std::string& host, const std::string& port);
	TcpStream(TcpStream&) = delete;
	TcpStream(TcpStream&&) = delete;
	TcpStream& operator=(TcpStream&&) = delete;
	TcpStream& operator=(TcpStream&) = delete;
	
	virtual ~TcpStream() = default;

	// Stream implementation
	void			Write(const void* data, size_t count) override;
	
	void			Read(void* data, size_t count) override;
	
	// IStreamProvider implementation
	void			FlushAsync(const OnActionCallback& onFlushCallback) override;
	
	void			Flush() override;

	bool			IsOpen() const override;
	
private:
	AsioStream		m_tcpStream;
};
	
}

