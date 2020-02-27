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

	/**
	 * \brief It tries to asynchronously write to the stream the information accumulated in the stream buffer,
	 * it does not block the thread from which it is called, at the end of the operation, it calls the callback function
	 * \param onFlushCallback callback function, will be called at the end of the operation
	 */
	virtual void FlushAsync(const OnActionCallback& onFlushCallback) = 0;

	/**
	 * \brief tries to synchronously write to the stream the information accumulated in the stream buffer,
	 * blocks the thread from which it is called
	 */
	virtual void Flush() = 0;
	
	/**
	 * \brief synchronously checks the connection
	 * \return connection condition
	 */
	virtual bool IsOpen() const = 0;
};
	
}
