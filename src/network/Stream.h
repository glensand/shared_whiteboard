/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <type_traits>
#include <memory>
#include <functional>

namespace Net
{

template <typename T>
using OnReadCallback = std::function<void(T&& object)>;
using OnActionCallback = std::function<void(size_t availableBytes)>;
	
class Stream
{
public:
	virtual ~Stream() = default;

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
    [[nodiscard]] virtual bool IsOpen() const = 0;

    /**
	 * \brief Closing the connection, whole data from queue will be removed completely
	 */
	virtual void Close() = 0;
	
	/**
	 * \brief casts object to WT, and writes it to the stream as WT argument
	 * \tparam T base argument type
	 * \tparam WT type to which argument will be cast before writing
	 * \param object data to be written 
	 */
	template <typename WT, typename T>
	void WriteAs(const T& object);

	/**
	 * \brief reads some data as RT, casts it into T and returns
	 * \tparam T required argument type 
	 * \tparam RT type of containing in the stream argument
	 * \return argument which was read
	 */
	template <typename RT, typename T>
	T ReadAs();

	/**
	 * \brief writes argument to the stream <as is>, argument should be of integral type
	 * \tparam T 
	 * \param object 
	 * \return 
	 */
	template <typename T>
	void Write(const T& object);

	/**
	 * \brief 
	 * \tparam T 
	 * \param object 
	 * \param callback 
	 */
	template <typename T>
	void WriteAsync(const T& object, const std::function<void()>& callback);

	/**
	 * \brief reads argument from stream, argument must be of integral type
	 * \tparam T 
	 * \return 
	 */
	template <typename T>
	T Read();

	/**
	 * \brief tries to asynchronously read data of the specified type from the stream
	 * \tparam T data type must be integral,
	 * or a pointer to a class object, with the DeserializeFrom method implemented
	 * \param callback 
	 */
	template <typename T>
	void ReadAsync(const OnReadCallback<T>& callback);
	
	/**
	 * \brief writes row data to the stream
	 * \param data pointer to the data block
	 * \param count 
	 */
	virtual void Write(const void* data, size_t count) = 0;

	/** 
	 * \brief reads row data from stream 
	 * \param data 
	 * \param count 
	 */
	virtual void Read(void* data, size_t count) = 0;

protected:
	/**
	 * \brief asynchronously starts the passed function
	 * \param func function to be launched at the end of asynchronous operation
	 */
	virtual void LaunchAsync(const std::function<void()>& func) = 0;
};

template <typename WT, typename T>
void Stream::WriteAs(const T& object)
{
	const auto writableObject = static_cast<WT>(object);
	Write(&writableObject, sizeof writableObject);
}

template <typename RT, typename T>
T Stream::ReadAs()
{
	RT readObject;
	Read(&readObject, sizeof readObject);
	return static_cast<T>(readObject);
}

template <typename T>
void Stream::Write(const T& object)
{
	if constexpr (std::is_integral_v<T>)
	{
		Write(&object, sizeof object);
	}
	else
	{
		object.SerializeTo(*this);
	}
}

template <typename T>
void Stream::WriteAsync(const T& object, const std::function<void()>& callback)
{
	LaunchAsync([=]()
		{
			Write(object);
			callback();
		});
}

template <typename T>
T Stream::Read()
{
	T object;
	
	if constexpr (std::is_integral_v<T>)
	{
		Read(&object, sizeof(object));
	}
	else
	{
		object.DeserializeFrom(*this);
	}
	
	return object;
}

template <typename T>
void Stream::ReadAsync(const OnReadCallback<T>& callback)
{
	LaunchAsync([this]()
		{
			callback(Read<T>);
		});
}

using StreamPtr = std::unique_ptr<Stream>;
	
}

