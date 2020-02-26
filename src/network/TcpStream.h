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

#include "BaseStream.h"
#include "IStreamProvider.h"

#include "ITcpClient.h"

namespace Net
{

class TcpStream final : public BaseStream, public IStreamProvider
{
public:
	TcpStream(TcpClient&& client);
	TcpStream(TcpStream&) = delete;
	TcpStream(TcpStream&&) = delete;
	TcpStream& operator=(TcpStream&&) = delete;
	TcpStream& operator=(TcpStream&) = delete;
	
	virtual ~TcpStream() = default;

	// IStreamProvider implementation
	void			FlushAsync(const OnActionCallback& onFlushCallback) override;
	
	void			Flush() override;

	void			AsyncWaitForData(const OnActionCallback& onReceiveCallback) override;
	
private:
	void			TryConnection();
	
	std::string		m_buffer;

	TcpClient		m_tcpClient;
	std::string		m_host;
	std::string		m_port;
};
	
}

