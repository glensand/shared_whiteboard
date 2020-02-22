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
		std::cout << "on draw callback" << std::endl;
		Send(shape);
	};

	m_onReadCallback = [this](const boost::system::error_code&, size_t)
	{
		std::cout << "on read callback" << std::endl;
		Receive();
	};

	m_OnSentCallback = [this](const boost::system::error_code&, size_t)
	{
		std::cout << "on sent callback" << std::endl;
		OnSentCallback();
	};
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Run()
{
	m_whiteBoard->RegisterOnDrawCallback(m_onDrawCallback);
	
	m_tcpClient.Connect();
	m_tcpClient.AwaitData(m_onReadCallback);

	m_whiteBoard->Open();
	m_whiteBoard->Close();
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Send(const Shape& shape)
{
	m_writeStream.clear();
	ShapeSerializer::Instance().Serialize(m_writeStream, shape);
	m_tcpClient.WriteAsync(m_writeStream, m_OnSentCallback);
}
//------------------------------------------------------------------------------
void SharedWhiteboard::Receive()
{
	std::stringstream stream;
	m_tcpClient.Receive(stream);
	const auto shape = ShapeSerializer::Instance().Deserialize(stream);
	m_whiteBoard->Draw(shape);
}
//------------------------------------------------------------------------------	
void SharedWhiteboard::OnSentCallback()
{
	std::cout << "Sent" << std::endl;
}
//------------------------------------------------------------------------------	
}

}
