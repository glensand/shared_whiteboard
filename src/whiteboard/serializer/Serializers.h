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

class SerializerBase : public ISerializerInner
{
public:
	Package				Serialize(const Shape& shape) const final;
	Shape				Deserialize(const Package& pcg) const final;

	void				AddNext(Serializer&& ser) final;
	const Serializer&	GetNext() final;
	
protected:
	virtual	bool		CanBeProcessed(ShapeType type) const = 0;

	virtual Package		SerializeImpl(const Shape& shape) const = 0;
	virtual Shape		DeserializeImpl(const Package& pcg) const = 0;

	template<typename T>
	static Shape		DeserializeBase(const Package& pcg);

	template<typename T>
	static Package		SerializeBase(const Shape& shape);

private:
	Serializer			m_next;
};

//TODO:: real serialization should be added
template <typename T>
Shape SerializerBase::DeserializeBase(const Package& pcg)
{
	Shape shape = std::make_shared<T>();
	const auto rowShape = reinterpret_cast<uint8_t*>(shape.get());
	const auto* pcgData = reinterpret_cast<const uint8_t*>(pcg.RowData);
	const auto* begin = pcgData + sizeof(size_t);

	std::copy(begin, begin + pcg.Emount - sizeof(size_t), rowShape);

	return shape;
}

template <typename T>
Package SerializerBase::SerializeBase(const Shape& shape)
{
	Package pcg{};

	pcg.Emount = sizeof(T) + sizeof(size_t);
	const auto* begin = reinterpret_cast<const uint8_t*>(shape.get());

	const auto data = reinterpret_cast<size_t*>(pcg.RowData);

	std::copy(begin, begin + pcg.Emount, data + 1);

	return pcg;
}
	
}
