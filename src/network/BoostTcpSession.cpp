﻿#include "BoostTcpSession.h"
#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------
BoostTcpSession::BoostTcpSession(Service& service)
	: m_socket(service)
	, m_isInitialized(false)
{
	m_buffer.resize(1000);
}
//------------------------------------------------------------------------------
size_t BoostTcpSession::WriteSome(const char* data, size_t count)
{
	return m_socket.write_some(boost::asio::buffer(data, count));
}
//------------------------------------------------------------------------------
size_t BoostTcpSession::Write(const char* data, size_t count)
{
	return write(m_socket, boost::asio::buffer(data, count));
}
//------------------------------------------------------------------------------
void BoostTcpSession::WriteAsync(const char* data, size_t count, const OnActionCallback& callback)
{
	async_write(m_socket, boost::asio::buffer(data, count),
		[callback](const boost::system::error_code& code, size_t count)
		{
			callback(count);
			std::cout << "BoostTcpSession::WriteAsync: " << code << std::endl;
		});
}
//------------------------------------------------------------------------------
size_t BoostTcpSession::ReadSome(std::ostream& stream)
{
	const auto count = m_socket.read_some(boost::asio::buffer(m_buffer));
	stream.write(m_buffer.data(), count);
	return count;
}
//------------------------------------------------------------------------------
size_t BoostTcpSession::Read(std::ostream& stream, size_t count)
{
	m_buffer.resize(count);
	return read(m_socket, boost::asio::buffer(m_buffer));
}
//------------------------------------------------------------------------------
void BoostTcpSession::AwaitData(const OnActionCallback& callback)
{
	// when this method is used in BoostTcpClient a three-layer lambda is obtained
	m_socket.async_read_some(boost::asio::buffer(m_buffer),
		[callback](const boost::system::error_code& code, size_t count)
		{
			// TODO:: create more appropriate way to use error code
			std::cout << "BoostTcpSession::received: " << code << std::endl;
			callback(count);
		});
}
//------------------------------------------------------------------------------
void BoostTcpSession::Receive(std::ostream& stream, size_t count) const
{
	stream.write(m_buffer.data(), count);
}
//------------------------------------------------------------------------------
BoostTcpSession::Socket& BoostTcpSession::GetSocket()
{
	return m_socket;
}
//------------------------------------------------------------------------------
const BoostTcpSession::Socket& BoostTcpSession::GetSocket() const
{
	return m_socket;
}
//------------------------------------------------------------------------------
void BoostTcpSession::SetInitialized(bool init)
{
	m_isInitialized = init;
}
//------------------------------------------------------------------------------
bool BoostTcpSession::IsInitialized() const
{
	return m_isInitialized;
}
//------------------------------------------------------------------------------
}
