//------------------------------------------------------------------------------
// ITcpClient.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 21.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------

#pragma once

#include <functional>
#include <ostream>

namespace Net
{

using OnActionCallback = std::function<void(size_t)>;
	
/**
 * \brief
 *		The interface of the flexible TCP client sets
 *		the contract for synchronous and asynchronous clients
 */
class ITcpClient
{
public:
	ITcpClient() = default;

	virtual ~ITcpClient() = default;

					/**
					 * \brief Trying to establish a connection with the specified endpoint
					 * \param host - ip address or domain name of the server
					 * \param port - port on which the server is listening
					 * \return if the connection is established successfully returns true
					 */
	virtual bool	Connect(const std::string& host, const std::string& port) = 0;

					/**
					 * \brief	Checks if the connection is live
					 * \return true, if the socket is alive
					 */
	virtual bool	IsOpen() const = 0;
	
					/**
					 * \brief Closes the connection
					 */
	virtual void	Close() = 0;

					/**
					 * \brief Starts the asynchronous command handler.
					 *	A call to this method is necessary for asynchronous read / write operation.
					 *	The handler will be launched in a separate thread, which will block.
					 */
	virtual void	RunAsyncHandler() = 0;

					/**
					 * \brief Stops the asynchronous handler.
					 *	Terminates all asynchronous operations.
					 *	Callbacks will be instantly called for all running asynchronous commands. It also destroys a running thread.
					 */
	virtual void	StopAsyncHandler() = 0;
	
					/**
					 * \brief Trying to write asynchronously passed data to the socket 
					 * \param data - pointer to the block of the data, the pointer must remain valid until the operation is completed
					 * \param count - amount of data to be send
					 * \param callback - the handler to be called at the end of operation
					 */
	virtual void	WriteAsync(const char* data, size_t count, const OnActionCallback& callback) = 0;
					
					/**
					 * \brief Trying to write some information to a socket. Function call blocks thread
					 * \param data - pointer to the data block
					 * \param count - count of bytes, containing in the data block
					 * \return count of written bytes
					 */
	virtual size_t	WriteSome(const char* data, size_t count) = 0;
	
					/**
					 * \brief Trying to write all passed data. Function call blocks thread.
					 * \param data - pointer to the data block
					 * \param count - count of bytes to be wrote
					 */
	virtual void	Write(const char* data, size_t count) = 0;

					/**
					 * \brief Reads a specific number of bytes from a socket,
					 * blocks the stream from which it is called
					 * \param stream - stream for writing read data
					 * \param count - number of bytes to be read
					 * \return number of bytes read successfully
					 */
	virtual size_t	Read(std::ostream& stream, size_t count) = 0;
	
					/**
					 * \brief	Attempts to read a number of bytes from a socket.
					 *	The operation completes after reading the whole package.
					 * \param stream - stream, to be filled with received data
					 * \return - count of read bytes 
					 */
	virtual size_t	ReadSome(std::ostream& stream) = 0;

					/**
					 * \brief Asynchronously reads available data from the socket, and writes it to the passed stream.
					 * Calls the handler upon completion
					 * \param stream 
					 * \param callback - handler which will be called when reading ends
					 */
	virtual void	ReadSomeAsync(std::ostream& stream, const OnActionCallback& callback) = 0;
	
					/**
					 * \brief Asynchronously reads available data from the socket.
					 * Calls the handler upon completion
					 * \param callback - handler which will be called when reading ends
					 */
	virtual void	AwaitData(const OnActionCallback& callback) = 0;

					/**
					 * \brief Reads bytes previously received
					 * from the socket into the stream.
					 * \param stream - stream for writing read data
					 * \param count - count of writing bytes
					 */
	virtual void	Receive(std::ostream& stream, size_t count) const = 0;
};

/**
 * \brief Recommended alias
 */
using TcpClient = std::unique_ptr<ITcpClient>;
	
}
