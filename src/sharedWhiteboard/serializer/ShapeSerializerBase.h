//------------------------------------------------------------------------------
// SerializerBase.h
// Common shape serializers, implements chain
// Copyright (c) 2020 glensand
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
	void				Serialize(std::ostream& stream, const Shape& shape) const final;
	Shape				Deserialize(std::istream& stream) const final;

	void				AddNext(Serializer&& ser) final;
	const Serializer&	GetNext() const final;
	
protected:
	Shape				Deserialize(std::istream& stream, ShapeType type) const final;
	
	static ShapeType	DeserializeType(std::istream& stream);
	static void			SerializeType(std::ostream& stream, ShapeType type);
	
	virtual	bool		CanBeProcessed(ShapeType type) const = 0;

	virtual void		SerializeImpl(std::ostream& stream, const Shape& shape) const = 0;
	virtual Shape		DeserializeImpl(std::istream& stream) const = 0;

private:
	Serializer			m_next;
};
	
}
