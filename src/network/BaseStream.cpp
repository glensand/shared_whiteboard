#include "BaseStream.h"

namespace Net
{
//------------------------------------------------------------------------------	
void BaseStream::Write(const void* data, size_t count)
{
	m_stream.write(reinterpret_cast<const char*>(data), count);
}
//------------------------------------------------------------------------------
void BaseStream::Read(void* data, size_t count)
{
	m_stream.read(reinterpret_cast<char*>(data), count);
}
//------------------------------------------------------------------------------	
std::string BaseStream::GetString() const
{
	return m_stream.rdbuf()->str();
}
//------------------------------------------------------------------------------	
}
