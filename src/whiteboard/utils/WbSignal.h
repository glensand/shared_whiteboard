//------------------------------------------------------------------------------
// WbSignal.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include <functional>

namespace wboard
{

class IWbSignal
{
public:
	virtual ~IWbSignal() = default;

	virtual void	Connect(const std::function<void()>& slot) = 0;

	virtual void	Emit() = 0;
};

using WbSignal = std::unique_ptr<IWbSignal>;
}

