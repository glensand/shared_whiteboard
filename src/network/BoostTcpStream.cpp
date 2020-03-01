#include "BoostTcpStream.h"

namespace Net
{
//------------------------------------------------------------------------------
BoostTcpStream::BoostTcpStream(const std::string& host, const std::string& port)
		: m_tcpStream(host, port)
{
}
//------------------------------------------------------------------------------
void BoostTcpStream::Write(const void* data, size_t count)
{
	m_tcpStream.write(reinterpret_cast<const char*>(data), count);
}
//------------------------------------------------------------------------------
void BoostTcpStream::Read(void* data, size_t count)
{
	m_tcpStream.read(reinterpret_cast<char*>(data), count);
}
//------------------------------------------------------------------------------
void BoostTcpStream::FlushAsync(const OnActionCallback& onFlushCallback)
{
	LaunchAsync([this, onFlushCallback]()
		{
			m_tcpStream.flush();
			onFlushCallback(0);
		});
}
//------------------------------------------------------------------------------
void BoostTcpStream::Flush()
{
	m_tcpStream.flush();
}
//------------------------------------------------------------------------------
bool BoostTcpStream::IsOpen() const
{
	return m_tcpStream.good();
}
//------------------------------------------------------------------------------	
void BoostTcpStream::LaunchAsync(const std::function<void()>& func)
{
	auto future = std::async(std::launch::async, func);
}
//------------------------------------------------------------------------------	
}
