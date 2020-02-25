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
		m_socket->open(boost::asio::ip::tcp::v4());
		m_socket->set_option(option);
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
void BoostTcpClient::Close() const
{
	m_socket->close();
}
//------------------------------------------------------------------------------
void BoostTcpClient::RunService()
{
	m_serviceThread = std::thread([this]
		{
			m_service.run();
		});
	m_serviceThread.detach();
}
//------------------------------------------------------------------------------
void BoostTcpClient::StopService()
{
	m_service.stop();
}
//------------------------------------------------------------------------------
void BoostTcpClient::WriteAsync(const char* data, size_t count, const OnActionCallback& callback) const
{
	async_write(*m_socket, boost::asio::buffer(data, count), callback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::Write(const char* data, size_t count) const
{
	m_socket->write_some(boost::asio::buffer(data, count));
}
//------------------------------------------------------------------------------
size_t BoostTcpClient::Read(std::stringstream& stream)
{
	const auto size = m_socket->read_some(boost::asio::buffer(m_buffer, bufferSize));
	stream.write(m_buffer, size);
	return size;
}
//------------------------------------------------------------------------------
void BoostTcpClient::AwaitData(const OnActionCallback& callback)
{
	std::cout << "BoostTcpClient::AwaitData" << std::endl;
	m_socket->async_read_some(boost::asio::buffer(m_buffer, bufferSize), callback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::Receive(std::stringstream& stream, size_t count) const
{
	stream.write(m_buffer, count);
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
void BoostTcpClient::SetEndpoint(const std::string& host, const std::string& port)
{
	m_host = host;
	m_port = port; 
}
//------------------------------------------------------------------------------
}
