#include "BoostTcpSession.h"

namespace Net
{
//------------------------------------------------------------------------------
BoostTcpSession::BoostTcpSession(Service& service)
	: m_socket(service)
	, m_isInitialized(false)
{
}
//------------------------------------------------------------------------------
void BoostTcpSession::WriteAsync(const char* data, size_t count, const OnActionCallback& errorCallback)
{
	async_write(m_socket, boost::asio::buffer(data, count), errorCallback);
}
//------------------------------------------------------------------------------
void BoostTcpSession::AwaitData(const OnActionCallback& callback)
{
	m_socket.async_read_some(boost::asio::buffer(m_buffer, bufferSize), callback);
}
//------------------------------------------------------------------------------
void BoostTcpSession::Receive(std::stringstream& stream, size_t count) const
{
	stream.write(m_buffer, count);
}
//------------------------------------------------------------------------------
BoostTcpSession::Socket& BoostTcpSession::GetSocket()
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
