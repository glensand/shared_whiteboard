//------------------------------------------------------------------------------
// ArgumentFactory.h
//
// ArgumentFactory implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 29.02.2020
// Author: glensand
//------------------------------------------------------------------------------

#pragma once

#include <unordered_map>
#include <functional>

#include "IArgument.h"

namespace wboard
{

enum class EArgumentType;
	
class ArgumentFactory final
{
using ArgumentCreator = std::function<ArgumentPtr()>;
public:

	ArgumentFactory(const ArgumentFactory&) = delete;
	ArgumentFactory(ArgumentFactory&&) = delete;
	ArgumentFactory&  operator=(ArgumentFactory&) = delete;
	ArgumentFactory&  operator=(ArgumentFactory&&) = delete;
	~ArgumentFactory() = default;

	static ArgumentFactory& Instance();
	
	ArgumentPtr				NewArgument(EArgumentType type);

	template <typename TArgument>
	void		RegisterArgument(EArgumentType type);

private:
	ArgumentFactory();
	std::unordered_map<EArgumentType, ArgumentCreator>	m_creators;
};

template <typename TArgument>
void ArgumentFactory::RegisterArgument(EArgumentType type)
{
	m_creators.emplace(type, [=]()
		{
			return std::make_unique<TArgument>();
		});
}
}
