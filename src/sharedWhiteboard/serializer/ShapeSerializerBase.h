//------------------------------------------------------------------------------
// SerializerBase.h
// Common shape serializers, implements chain
// Copyright (c) 2020 Bezborodov Gleb
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include "ISerializerInner.h"

namespace wboard
{

class ShapeSerializerBase : public ISerializerInner
{
public:
	void				Serialize(Net::Stream& stream, const Shape& shape) const final;
	Shape				Deserialize(Net::Stream& stream) const final;

	void				AddNext(Serializer&& ser) final;
	const Serializer&	GetNext() const final;
	
protected:
	Shape				Deserialize(Net::Stream& stream, ShapeType type) const final;
	
	static ShapeType	DeserializeType(Net::Stream& stream);
	static void			SerializeType(Net::Stream& stream, ShapeType type);
	
	virtual	bool		CanBeProcessed(ShapeType type) const = 0;

	virtual void		SerializeImpl(Net::Stream& stream, const Shape& shape) const = 0;
	virtual Shape		DeserializeImpl(Net::Stream& stream) const = 0;

private:
	Serializer			m_next;
};
	
}
