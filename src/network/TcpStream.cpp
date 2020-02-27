#include "TcpStream.h"

namespace Net
{
//------------------------------------------------------------------------------
TcpStream::TcpStream(const std::string& host, const std::string& port)
		: m_tcpStream(host, port)
{
}
//------------------------------------------------------------------------------
void TcpStream::Write(const void* data, size_t count)
{
	m_tcpStream.write(reinterpret_cast<const char*>(data), count);
}
//------------------------------------------------------------------------------
void TcpStream::Read(void* data, size_t count)
{
	m_tcpStream.read(reinterpret_cast<char*>(data), count);
}
//------------------------------------------------------------------------------
void TcpStream::FlushAsync(const OnActionCallback& onFlushCallback)
{
	// TODO:: needs implementation
}
//------------------------------------------------------------------------------
void TcpStream::Flush()
{
	m_tcpStream.flush();
}
//------------------------------------------------------------------------------
bool TcpStream::IsOpen() const
{
	return m_tcpStream.good();
}
//------------------------------------------------------------------------------	
}
