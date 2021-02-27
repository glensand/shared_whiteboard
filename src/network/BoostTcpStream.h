/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

