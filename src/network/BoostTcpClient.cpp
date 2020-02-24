#include "BoostTcpClient.h"

#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------
bool BoostTcpClient::Connect()
{
	try
	{
		boost::asio::ip::tcp::resolver resolver(m_service);
		const auto endpoints = resolver.resolve(m_host, m_port);
		const boost::asio::ip::tcp::no_delay option(true);
		m_socket = std::make_unique<Socket>(m_service);
		m_socket->set_option(option);
		boost::asio::connect(*m_socket, endpoints);

		return true;
	}
	catch (std::exception & e)
	{
		std::cerr << "Connect failed: " << e.what() << std::endl;
		return false;
	}
}
//------------------------------------------------------------------------------
void BoostTcpClient::WriteAsync(const std::istream& stream, const OnActionCallback& errorCallback) const
{
	async_write(*m_socket, boost::asio::buffer(stream.rdbuf(), stream.gcount()), errorCallback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::AwaitData(const OnActionCallback& callback)
{
	m_socket->async_read_some(boost::asio::buffer(m_buffer, bufferSize), callback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::Receive(std::ostream& stream) const
{
	stream << &m_buffer;
}
//------------------------------------------------------------------------------
BoostTcpClient::Socket& BoostTcpClient::GetSocket() const
{
	return *m_socket;
}
//------------------------------------------------------------------------------
}
