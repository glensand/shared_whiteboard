//------------------------------------------------------------------------------
// Request.h
//
// SharedWhiteboard implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 21.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

namespace Net
{
class Stream;
}

namespace wboard
{

class Request
{
public:

	virtual ~Request() = default;

	void	SerializeTo(Net::Stream& stream);
	
	void	DeserializeFrom(Net::Stream& stream);
};

}
