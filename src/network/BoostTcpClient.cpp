#include "BoostTcpClient.h"

#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------
BoostTcpClient::BoostTcpClient(const std::string& host, const std::string& port)
	: m_isInitialized(false)
    , m_host(host)
	, m_port(port)
{

}
//------------------------------------------------------------------------------
bool BoostTcpClient::Connect()
{
	try
	{
		boost::asio::ip::tcp::resolver resolver(m_service);
		const auto endpoints = resolver.resolve(boost::asio::ip::tcp::v4(), m_host, m_port);
		const boost::asio::ip::tcp::no_delay option(true);
		m_socket = std::make_unique<Socket>(m_service);
		//m_socket->set_option(option);
		boost::asio::connect(*m_socket, endpoints);

		m_isInitialized = true;

		std::cout << "Connected" << std::endl;
		return true;
	}
	catch (std::exception & e)
	{
		std::cerr << "Connect failed: " << e.what() << std::endl;
		return false;
	}
}
//------------------------------------------------------------------------------
void BoostTcpClient::WriteAsync(const char* data, size_t count, const OnActionCallback& errorCallback) const
{
	async_write(*m_socket, boost::asio::buffer(data, count), errorCallback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::AwaitData(const OnActionCallback& callback)
{
	std::cout << "BoostTcpClient::AwaitData" << std::endl;
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
void BoostTcpClient::SetInitialized(bool init)
{
	m_isInitialized = init;
}
//------------------------------------------------------------------------------
bool BoostTcpClient::IsInitialized() const
{
	return m_isInitialized;
}
//------------------------------------------------------------------------------
}
