#include "ArgumentFactory.h"

#include "EArgumentType.h"
#include "ArgumentShape.h"

namespace wboard
{
//------------------------------------------------------------------------------	
ArgumentFactory& ArgumentFactory::Instance()
{
	static ArgumentFactory instance;
	return instance;
}
//------------------------------------------------------------------------------
ArgumentPtr ArgumentFactory::NewArgument(EArgumentType type)
{
	const auto creator = m_creators.find(type);
	if (creator == m_creators.end())
		throw std::exception("An unknown argument type was passed");

	return creator->second();
}
//------------------------------------------------------------------------------
ArgumentFactory::ArgumentFactory()
{
	RegisterArgument<ArgumentShape>(EArgumentType::Shape);
}
//------------------------------------------------------------------------------
}
