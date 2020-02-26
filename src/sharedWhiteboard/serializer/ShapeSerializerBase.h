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
	void				Serialize(std::stringstream& stream, const Shape& shape) const final;
	Shape				Deserialize(std::stringstream& stream) const final;

	void				AddNext(Serializer&& ser) final;
	const Serializer&	GetNext() const final;
	
protected:
	Shape				Deserialize(std::stringstream& stream, ShapeType type) const final;
	
	static ShapeType	DeserializeType(std::stringstream& stream);
	static void			SerializeType(std::stringstream& stream, ShapeType type);
	
	virtual	bool		CanBeProcessed(ShapeType type) const = 0;

	virtual void		SerializeImpl(std::stringstream& stream, const Shape& shape) const = 0;
	virtual Shape		DeserializeImpl(std::stringstream& stream) const = 0;

private:
	Serializer			m_next;
};
	
}
