//------------------------------------------------------------------------------
// ITcpServer.h
//
// ITcpServer implements...
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

using ServerOnActionCallback = std::function<void(int clientId)>;
using OnActionCallback = std::function<void(size_t)>;
	
class ITcpServer
{
public:
	virtual ~ITcpServer() = default;

					/**
					 * \brief Asynchronously waits for new connections, with a new connection, calls a callback
					 * \param connectionHandler - on connection callback
					 */
	virtual void	AwaitConnections(const ServerOnActionCallback& connectionHandler) = 0;
	
					/**
					 * \brief asynchronously waits for data to be received;
					 * when it receives a certain amount, it calls a callback
					 * \param dataReceiveHandler
					 */
	virtual void	AwaitData(const ServerOnActionCallback& dataReceiveHandler) = 0;
	
					/**
					 * \brief 
					 * \param stream will be used to write all received data
					 * \param clientId 
					 */
	virtual void	Receive(std::ostream& stream, int clientId) = 0;

					/**
					 * \brief Trying to send information to the given client
					 * \param data 
					 * \param size 
					 * \param clientId unique client identifier
					 */
	virtual void	Send(const void* data, size_t size, int clientId) = 0;

					/**
					 * \brief 
					 * \param data 
					 * \param size 
					 * \param clientId 
					 * \param callback 
					 */
	virtual void	SendAsync(const void* data, size_t size, int clientId, const OnActionCallback& callback) = 0;
	
					/**
					 * \brief 
					 * \param data 
					 * \param size 
					 */
	virtual void	Send(const void* data, size_t size) = 0;

					/**
					 * \brief 
					 * \param data 
					 * \param size 
					 */
	virtual void	SendAsync(const void* data, size_t size) = 0;
};
	
}
