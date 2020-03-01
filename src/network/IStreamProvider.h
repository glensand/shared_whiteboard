//------------------------------------------------------------------------------
// StreamProvider.h
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 27.02.2020
// Author: glensand
//------------------------------------------------------------------------------

#pragma once

#include <functional>

namespace Net
{

using OnActionCallback = std::function<void(size_t availableBytes)>;
	
/**
 * \brief Provides an interface for basic flow operations
 */
class IStreamProvider
{
public:
	virtual ~IStreamProvider() = default;


};
	
}
