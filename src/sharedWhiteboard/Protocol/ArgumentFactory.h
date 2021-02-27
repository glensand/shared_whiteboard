/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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
