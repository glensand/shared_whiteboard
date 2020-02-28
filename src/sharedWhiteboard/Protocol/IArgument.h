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

namespace Net
{
class Stream;
}

namespace wboard
{

class IArgument
{
public:
	virtual ~IArgument() = default;

	virtual void	SerializeTo(Net::Stream& stream) const = 0;

	virtual void	DeserializeFrom(Net::Stream& stream) = 0;
};

using Argument = std::unique_ptr<IArgument>;
	
}
