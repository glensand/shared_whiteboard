//------------------------------------------------------------------------------
// ITcpClient.h
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 21.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include <string>
#include <functional>
#include <istream>

namespace Net
{
class ITcpClient
{
public:
	virtual ~ITcpClient();

	virtual bool	Connect() = 0;

	virtual void	WriteAsync(const void* data, size_t count, const std::function<void(int)>& errorCallback) = 0;

	virtual void	AwaitData(const std::function<void(const void* data, size_t count)>& callback) = 0;
	
	virtual void	Receive(std::ostream&) const = 0;
};

}
