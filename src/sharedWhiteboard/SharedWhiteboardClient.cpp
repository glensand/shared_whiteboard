#include "SharedWhiteboardClient.h"

#include "whiteboard/WhiteBoardCV.h"
#include "serializer/ShapeSerializer.h"

#include <sstream>
#include <iostream>
#include <exception>
#include "Configure.h"

namespace wboard
{
namespace shared
{
//------------------------------------------------------------------------------
SharedWhiteboardClient::SharedWhiteboardClient(WhiteBoard&& wb, const std::string& host, const std::string& port)
	: m_whiteBoard(std::move(wb))
	, m_port(port)
	, m_host(host)
{
	m_onDrawCallback = [this](const Shape& shape)
	{
		Send(shape);
	};

	m_onReadCallback = [this](size_t size)
	{
		if constexpr (DEBUG_PRINT)
			std::cout << "SharedWhiteboardClient m_onReadCallback: " << std::this_thread::get_id() << std::endl;
		
		Receive(size);
	};

	m_OnSentCallback = [this](size_t size)
	{
		if constexpr (DEBUG_PRINT)
			std::cout << "m_OnSentCallback count: " << size << std::endl;
		
		OnSentCallback();
	};
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::Run()
{
	if(!m_tcpClient.Connect(m_host, m_port))
	{
		throw std::exception("Cant connect to the given endpoint");
	}
	
	m_tcpClient.RunAsyncHandler();
	m_tcpClient.AwaitData(m_onReadCallback);
	
	m_whiteBoard->RegisterOnDrawCallback(m_onDrawCallback);
	m_whiteBoard->Open();
	
	m_whiteBoard->Close();
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::Send(const Shape& shape)
{
	std::stringstream stream;
	
	ShapeSerializer::Instance().Serialize(stream, shape);
	m_writeBuffer = stream.rdbuf()->str();
	m_tcpClient.WriteAsync(reinterpret_cast<const char*>(m_writeBuffer.c_str()), m_writeBuffer.size(), m_OnSentCallback);

	if constexpr (DEBUG_PRINT)
	{
		std::cout << "SharedWhiteboard::Send()" << std::endl;
		std::cout << "m_writeStream size: " << m_writeBuffer.size() << std::endl;
	}
}
//------------------------------------------------------------------------------
void SharedWhiteboardClient::Receive(size_t count)
{
	std::stringstream stream;
	m_tcpClient.Receive(stream, count);

	if(stream.tellp() != 0)
	{
		const auto shape = ShapeSerializer::Instance().Deserialize(stream);
		m_whiteBoard->DrawShape(shape);
	}

	if constexpr (DEBUG_PRINT)
		std::cout << "SharedWhiteboardClient::Receive: " << std::this_thread::get_id() << std::endl;

	m_tcpClient.AwaitData(m_onReadCallback);
}
//------------------------------------------------------------------------------	
void SharedWhiteboardClient::OnSentCallback()
{
	if constexpr (DEBUG_PRINT)
		std::cout << "SharedWhiteboard::OnSentCallback()" << std::endl;
}
//------------------------------------------------------------------------------	
}

}
