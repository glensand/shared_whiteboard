#include "ArgumentContainer.h"

#include "sharedWhiteboard/Protocol/ArgumentFactory.h"
#include "sharedWhiteboard/Protocol/IArgument.h"
#include "network/Stream.h"
#include <algorithm>

namespace wboard
{
//------------------------------------------------------------------------------	
void ArgumentContainer::SerializeTo(Net::Stream& stream) const
{
	stream.WriteAs<size_t>(m_arguments.size());
	for (const auto& arg : m_arguments)
	{
		stream.WriteAs<size_t>(arg->Type());
		stream.Write(*arg);
	}
}
//------------------------------------------------------------------------------
void ArgumentContainer::DeserializeFrom(Net::Stream& stream)
{
	for(size_t i = 0; i < stream.Read<size_t>(); ++i)
	{
		m_arguments.emplace_back(ArgumentFactory::Instance().NewArgument(stream.ReadAs<size_t, EArgumentType>()));
		m_arguments.back()->DeserializeFrom(stream);
	}
}
//------------------------------------------------------------------------------
void ArgumentContainer::AddArgument(ArgumentPtr&& arg)
{
	m_arguments.emplace_back(std::move(arg));
}
//------------------------------------------------------------------------------
ArgumentPtr ArgumentContainer::FindArgument(const std::string& name) const
{
	const auto res = std::find_if(m_arguments.begin(), m_arguments.end(), [&](const ArgumentPtr& arg)
		{
			return arg->Name() == name;
		});
	if (res == m_arguments.end())
		throw std::exception("Argument with passed name not found");
	return *res;
}
//------------------------------------------------------------------------------
}