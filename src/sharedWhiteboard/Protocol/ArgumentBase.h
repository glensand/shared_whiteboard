//------------------------------------------------------------------------------
// CLASS.h
//
// CLASS implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: dd.mm.2020
// Author: glensand
//------------------------------------------------------------------------------

#pragma once

#include <string>

#include "IArgument.h"
#include "network/Stream.h"

namespace wboard
{

enum class EArgumentType;
	
template <typename TValue>
class ArgumentBase : public IArgument
{
public:

	ArgumentBase(EArgumentType type, const std::string& name = "", const TValue& value = TValue())
		: m_type(type),
		  m_value(value),
		  m_name(name)
	{
	}

	EArgumentType	Type() const final;

	TValue			RowValue() const;

	std::string		Name() const final;

	void			SerializeTo(Net::Stream& stream) const final;

	void			DeserializeFrom(Net::Stream& stream) final;

protected:
	virtual void	SerializeImpl(Net::Stream& /*stream*/) const {}
	virtual void	DeserializeImpl(Net::Stream& /*stream*/) const {}
	
private:
	/**
	 * \brief Argument type, argument should not serialize its oun type
	 */
	EArgumentType	m_type;

	TValue			m_value;

	std::string		m_name;
};

template <typename TValue>
EArgumentType ArgumentBase<TValue>::Type() const
{
	return m_type;
}

template <typename TValue>
TValue ArgumentBase<TValue>::RowValue() const
{
	return m_value;
}

template <typename TValue>
std::string ArgumentBase<TValue>::Name() const
{
	return m_name;
}

template <typename TValue>
void ArgumentBase<TValue>::SerializeTo(Net::Stream& stream) const
{
	stream.WriteAs<size_t>(m_name.size());
	stream.Write(m_name.c_str(), m_name.size());
	stream.Write(m_value);
}

template <typename TValue>
void ArgumentBase<TValue>::DeserializeFrom(Net::Stream& stream)
{
	const auto nameSize = stream.Read<size_t>();
	const auto rowName = new char[nameSize];
	stream.Read(rowName, nameSize);
	m_name = rowName;
	m_value = stream.Read<TValue>();
}
	
}
