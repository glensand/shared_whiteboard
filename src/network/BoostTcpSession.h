//------------------------------------------------------------------------------
// BoostTcpSession.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 21.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <boost/asio.hpp>
#include <memory>

// TODO:: move class declaration (aka ISession) to the specified interface
// inherit implementation from interface that interface
namespace Net
{

/**
 * \brief async operations callback alias
 */
using OnActionCallback = std::function<void(size_t)>;

/**
 * \brief 
 */
class BoostTcpSession final
{
	/**
	 * \brief Recommended asio socket alias
	 */
	using Socket = boost::asio::ip::tcp::socket;

	
	/**
	 * \brief Recommended asio async operations handler alias
	 */
	using Service = boost::asio::io_service;

public:
	BoostTcpSession(Service& service);

	~BoostTcpSession() = default;

			/**
			 * \brief delegate to the asio::write_some
			 * \param data - data to be send
			 * \param count - number of bytes to be send
			 * \return 
			 */
	size_t	WriteSome(const char* data, size_t count);
	
			/**
			 * \brief delegate to the asio::write
			 * \param data 
			 * \param count 
			 * \return 
			 */
	size_t	Write(const char* data, size_t count);

	
			/**
			 * \brief delegate to the asio::async_write
			 * \param data 
			 * \param count 
			 * \param errorCallback 
			 */
	void	WriteAsync(const char* data, size_t count, const OnActionCallback& errorCallback);

			/** 
			 * \brief delegate to the asio::async_write
			 * \param stream 
			 * \return 
			 */
	size_t	ReadSome(std::ostream& stream);

			/**
			 * \brief delegate to the asio::read
			 * \param stream 
			 * \param count 
			 * \return 
			 */
	size_t	Read(std::ostream& stream, size_t count);
	
			/** delegate to the asio::async_read_some, calls callback func if success
			 * \brief 
			 * \param callback 
			 */
	void	AwaitData(const OnActionCallback& callback);

			/** writes recently received data in the passed stream
			 * \brief 
			 * \param count 
			 */
	void	Receive(std::ostream&, size_t count) const;

			/**
			 * \brief sets initialization flag, it means the entire socket is connected
			 * successfully 
			 * \param init 
			 */
	void	SetInitialized(bool init);

			/** gets initialization flag state
			 * \brief 
			 * \return 
			 */
	bool	IsInitialized() const;

					/** gets row asio socket
					 * \brief 
					 * \return 
					 */
	Socket&			GetSocket();

					/** gets row asio socket
					 * \brief 
					 * \return 
					 */
	const Socket&	GetSocket() const;
	
private:
	Socket	m_socket;
	bool	m_isInitialized;

	std::vector<char>	m_buffer;
};

/**
 * \brief recommended boost session alias
 */
using Session = std::unique_ptr<BoostTcpSession>;

}
