//------------------------------------------------------------------------------
// IArgument.h
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 28.02.2020
// Author: glensand
//------------------------------------------------------------------------------
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
