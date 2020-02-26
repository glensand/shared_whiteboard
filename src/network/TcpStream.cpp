#include "TcpStream.h"

namespace Net
{
//------------------------------------------------------------------------------
TcpStream::TcpStream(TcpClient&& client)
		: m_tcpClient(std::move(client))
{
}
//------------------------------------------------------------------------------
void TcpStream::FlushAsync(const OnActionCallback& onFlushCallback)
{
	TryConnection();
	m_buffer = GetString();
	m_tcpClient->WriteAsync(m_buffer.c_str(), m_buffer.size(), onFlushCallback);
}
//------------------------------------------------------------------------------
void TcpStream::TryConnection()
{
	if (!m_tcpClient->IsOpen() && !m_tcpClient->Connect(m_host, m_port))
		throw std::exception("Cant establish connection with given host and port");
}
//------------------------------------------------------------------------------	
void TcpStream::Flush()
{
	TryConnection();
	m_buffer = GetString();
	m_tcpClient->Write(m_buffer.c_str(), m_buffer.size());
}
//------------------------------------------------------------------------------
void TcpStream::AsyncWaitForData(const OnActionCallback& onReceiveCallback)
{
	TryConnection();
	m_tcpClient->AwaitData([onReceiveCallback, this](size_t size)
		{
			m_tcpClient->Receive(m_stream, size);
			onReceiveCallback(size);
		});
}
//------------------------------------------------------------------------------	
}
