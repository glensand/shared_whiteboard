//------------------------------------------------------------------------------
// IStream.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 27.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <type_traits>
#include <functional>

namespace Net
{

template <typename T>
using OnReadCallback = std::function<void(T&& object)>;
	
class Stream
{
public:
	virtual ~Stream() = default;
	
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
		object->SerializeTo(*this);
	}
}

template <typename T>
void Stream::WriteAsync(const T& object, const std::function<void()>& callback)
{
	LaunchAsync([this]()
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
		object->DeserializeFrom(*this);
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

}

