/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include "IArgument.h"
#include <vector>
#include <string>

namespace Net
{
class Stream;
}

namespace wboard
{

class ArgumentContainer
{
public:

	ArgumentContainer() = default;
	virtual ~ArgumentContainer() = default;

	void	SerializeTo(Net::Stream& stream) const;
	void	DeserializeFrom(Net::Stream& stream);

	void	AddArgument(ArgumentPtr&& arg);
	
	template <typename TArgument, typename ...Args>
	void AddArgument(Args&&... args);

	template<typename TArgument, typename TValue>
	TValue FindArgumentValue(const std::string& name) const;

	ArgumentPtr FindArgument(const std::string& name) const;
	
private:
	std::vector<ArgumentPtr>	m_arguments;
};

template <typename TArgument, typename ... Args>
void ArgumentContainer::AddArgument(Args&&... args)
{
	m_arguments.emplace_back(std::make_unique<TArgument>(std::forward<Args>(args)...));
}

template<typename TArgument, typename TValue>
TValue ArgumentContainer::FindArgumentValue(const std::string& name) const
{
	const auto arg = FindArgument(name);
	return arg->Value<TValue>();
}
	
}

