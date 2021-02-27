/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <functional>
#include <ostream>

namespace Net
{

using ServerOnActionCallback = std::function<void(int clientId)>;
using OnActionCallback = std::function<void(size_t)>;
//using ServerOnReadCallback = std::function<void(int, size_t)>;
	
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
					 * \param clientId - unique client identifier
					 * \param dataReceiveHandler
					 */
	virtual void	AwaitData(int clientId, const OnActionCallback& dataReceiveHandler) = 0;
	
					/**
					 * \brief 
					 * \param stream will be used to write all received data
					 * \param clientId 
					 */
	virtual void	Receive(std::ostream& stream, size_t count, int clientId) = 0;

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
	virtual void	SendAsync(const void* data, size_t size, const OnActionCallback& callback) = 0;
};
	
}
