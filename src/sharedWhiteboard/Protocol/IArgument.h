/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <memory>
#include <string>

namespace Net
{
class Stream;
}

namespace wboard
{

enum class EArgumentType;
	
class IArgument
{
public:
	virtual ~IArgument() = default;

	virtual EArgumentType	Type() const = 0;
	
	virtual std::string		Name() const = 0;

	virtual void	SerializeTo(Net::Stream& stream) const = 0;

	virtual void	DeserializeFrom(Net::Stream& stream) = 0;
	
	template <typename T>
	T* As();

	template <typename TArgument, typename TValue>
	TValue Value() const;
};

template <typename T>
T* IArgument::As()
{
	return static_cast<T*>(this);
}

template <typename TArgument, typename TValue>
TValue IArgument::Value() const
{
	return static_cast<TArgument*>(this)->RowValue();
}

using ArgumentPtr = std::shared_ptr<IArgument>;
	
}
