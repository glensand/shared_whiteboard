﻿#include "ShapeSerializerBase.h"
#include "ShapeSerializer.h"

#include <ostream>
#include <istream>

namespace wboard
{
//------------------------------------------------------------------------------
void ShapeSerializerBase::Serialize(std::ostream& stream, const Shape& shape) const
{
	const auto type = shape->Type;
	if (CanBeProcessed(type))
	{
		SerializeType(stream, shape->Type);
		
		return SerializeImpl(stream, shape);
	}
	
	return m_next->Serialize(stream, shape);
}
//------------------------------------------------------------------------------
Shape ShapeSerializerBase::Deserialize(std::istream& stream) const
{
	const auto type = DeserializeType(stream);
	auto shape = Deserialize(stream, type);

	// Вонючий костыль, это надо убрать
	{
		shape->Type = type;
	}
	
	return shape;
}
//------------------------------------------------------------------------------
void ShapeSerializerBase::AddNext(Serializer&& ser)
{
	m_next = std::move(ser);
}
//------------------------------------------------------------------------------
const Serializer& ShapeSerializerBase::GetNext() const
{
	return m_next;
}
//------------------------------------------------------------------------------
Shape ShapeSerializerBase::Deserialize(std::istream& stream, ShapeType type) const
{
	if (CanBeProcessed(type)) return DeserializeImpl(stream);

	return GetNext()->Deserialize(stream, type);
}
//------------------------------------------------------------------------------
ShapeType ShapeSerializerBase::DeserializeType(std::istream& stream)
{
	uint8_t type = 0;
	stream.read(reinterpret_cast<char*>(type), sizeof type);
	return static_cast<ShapeType>(type);
}
//------------------------------------------------------------------------------
void ShapeSerializerBase::SerializeType(std::ostream& stream, ShapeType type)
{
	const auto writableType = static_cast<uint8_t>(type);
	stream.write(reinterpret_cast<const char*>(&writableType), sizeof(writableType));
}
//------------------------------------------------------------------------------
}
