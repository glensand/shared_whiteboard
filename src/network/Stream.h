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

namespace Net
{
	
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
	template <typename T, typename WT>
	void WriteAs(const T& object);

	/**
	 * \brief reads some data as RT, casts it into T and returns
	 * \tparam T required argument type 
	 * \tparam RT type of containing in the stream argument
	 * \return argument which was read
	 */
	template <typename T, typename RT>
	T ReadAs();

	/**
	 * \brief writes argument to the stream <as is>, argument should be of integral type
	 * \tparam T 
	 * \param object 
	 * \return 
	 */
	template <typename T>
	std::enable_if_t<std::is_integral_v<T>, void> Write(T object);

	/**
	 * \brief reads argument from stream, argument must be of integral type
	 * \tparam T 
	 * \return 
	 */
	template <typename T>
	std::enable_if_t<std::is_integral_v<T>, T> Read();
	
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
};

template <typename T, typename WT>
void Stream::WriteAs(const T& object)
{
	const auto writableObject = static_cast<WT>(object);
	Write(reinterpret_cast<const void*>(&writableObject), sizeof writableObject);
}

template <typename T, typename RT>
T Stream::ReadAs()
{
	RT readObject;
	Read(reinterpret_cast<void*>(&readObject), sizeof readObject);
	return static_cast<T>(readObject);
}

template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> Stream::Write(T object)
{
	Write(reinterpret_cast<void*>(&object), sizeof object);
}

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> Stream::Read()
{
	T res;
	Read(reinterpret_cast<void*>(&res), sizeof(res));
	return res;
}
	
}
