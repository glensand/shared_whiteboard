#include "BoostTcpClient.h"
#include "Configure.h"

#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------	
BoostTcpClient::BoostTcpClient()
	: m_session(m_service)
{
}
//------------------------------------------------------------------------------
BoostTcpClient::~BoostTcpClient()
{
	try
	{
		StopAsyncHandler();
		m_session.GetSocket().close();
	}
	catch(...)
	{
		std::cout << "BoostTcpClient::~BoostTcpClient() exception" << std::endl;
	}
}
//------------------------------------------------------------------------------
bool BoostTcpClient::Connect(const std::string& host, const std::string& port)
{
	try
	{
		boost::asio::ip::tcp::resolver resolver(m_service);
		const auto endpoints = resolver.resolve(boost::asio::ip::tcp::v4(), host, port);

		auto& socket = m_session.GetSocket();
		socket.open(boost::asio::ip::tcp::v4());

		{
			socket.set_option(boost::asio::ip::tcp::no_delay(true));
			socket.set_option(boost::asio::socket_base::keep_alive(true));
		}
		
		boost::asio::connect(m_session.GetSocket(), endpoints);

		if constexpr(DEBUG_PRINT)
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
bool BoostTcpClient::IsOpen() const
{
	return m_session.GetSocket().is_open();
}
//------------------------------------------------------------------------------
void BoostTcpClient::Close()
{
	m_session.GetSocket().close();
}
//------------------------------------------------------------------------------
void BoostTcpClient::RunAsyncHandler()
{
	m_serviceThread = std::make_unique<std::thread>([this]
		{
			m_service.run();
		});
	
	m_serviceThread->detach();
}
//------------------------------------------------------------------------------
void BoostTcpClient::StopAsyncHandler()
{
	m_service.stop();
	m_serviceThread.reset();
}
//------------------------------------------------------------------------------
void BoostTcpClient::WriteAsync(const char* data, size_t count, const OnActionCallback& callback)
{
	m_session.WriteAsync(data, count, callback);
}
//------------------------------------------------------------------------------
size_t BoostTcpClient::WriteSome(const char* data, size_t count)
{
	return m_session.WriteSome(data, count);
}
//------------------------------------------------------------------------------
void BoostTcpClient::Write(const char* data, size_t count)
{
	m_session.Write(data, count);
}
//------------------------------------------------------------------------------
size_t BoostTcpClient::ReadSome(std::ostream& stream)
{
	return m_session.ReadSome(stream);
}
//------------------------------------------------------------------------------
void BoostTcpClient::ReadSomeAsync(std::ostream& stream, const OnActionCallback& callback)
{
	m_session.AwaitData([this, &stream, &callback](size_t count)
		{
			Receive(stream, count);
			callback(count);
		});
}
//------------------------------------------------------------------------------
size_t BoostTcpClient::Read(std::ostream& stream, size_t count)
{
	return m_session.Read(stream, count);
}
//------------------------------------------------------------------------------
void BoostTcpClient::AwaitData(const OnActionCallback& callback)
{
	std::cout << "BoostTcpClient::AwaitData: " << std::this_thread::get_id() << std::endl;
	
	m_session.AwaitData(callback);
}
//------------------------------------------------------------------------------
void BoostTcpClient::Receive(std::ostream& stream, size_t count) const
{
	m_session.Receive(stream, count);
}
//------------------------------------------------------------------------------
}
