#include "SharedWhiteboard.h"

#include "whiteboard/WhiteBoardCV.h"
#include "serializer/ShapeSerializer.h"

#include <sstream>
#include <iostream>

namespace wboard
{
namespace shared
{
//------------------------------------------------------------------------------
SharedWhiteboard::SharedWhiteboard(WhiteBoard&& wb, const std::string& host, const std::string& port)
	: m_whiteBoard(std::move(wb))
	, m_tcpClient(host, port)
{
	m_onDrawCallback = [this](const Shape& shape)
	{
		Send(shape);
	};

	m_onReadCallback = [this](const boost::system::error_code&, size_t)
	{
		std::cout << "m_onReadCallback" << std::endl;
		
		Receive();
	};

	m_OnSentCallback = [this](const boost::system::error_code&, size_t)
	{
		OnSentCallback();
	};
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Run()
{
	m_tcpClient.Connect();
	m_tcpClient.RunService();
	m_tcpClient.AwaitData(m_onReadCallback);
	
	m_whiteBoard->RegisterOnDrawCallback(m_onDrawCallback);
	m_whiteBoard->Open();
	
	m_whiteBoard->Close();
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Send(const Shape& shape)
{
	m_writeStream = std::stringstream();
	
	ShapeSerializer::Instance().Serialize(m_writeStream, shape);
	m_tcpClient.WriteAsync(reinterpret_cast<const char*>(m_writeStream.rdbuf()), m_writeStream.tellp(), m_OnSentCallback);

	std::cout << "SharedWhiteboard::Send()" << std::endl;
	std::cout << "m_writeStream size: " << m_writeStream.tellp() << std::endl;
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Receive()
{
	std::stringstream stream;
	m_tcpClient.Receive(stream);

	if(stream.tellp() != 0)
	{
		const auto shape = ShapeSerializer::Instance().Deserialize(stream);
		m_whiteBoard->Draw(shape);
	}
	
	std::cout << "SharedWhiteboard::Receive()" << std::endl;

	m_tcpClient.AwaitData(m_onReadCallback);
}
//------------------------------------------------------------------------------	
void SharedWhiteboard::OnSentCallback()
{
	std::cout << "SharedWhiteboard::OnSentCallback()" << std::endl;
}
//------------------------------------------------------------------------------	
}

}
