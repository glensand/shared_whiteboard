#include "ShapeSerializerBase.h"
#include "ShapeSerializer.h"

#include "network/Stream.h"

namespace wboard
{
//------------------------------------------------------------------------------
void ShapeSerializerBase::Serialize(Net::Stream& stream, const Shape& shape) const
{
	const auto type = shape->Type;
	if (CanBeProcessed(type))
	{
		SerializeType(stream, type);
		
		return SerializeImpl(stream, shape);
	}
	
	return m_next->Serialize(stream, shape);
}
//------------------------------------------------------------------------------
Shape ShapeSerializerBase::Deserialize(Net::Stream& stream) const
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
Shape ShapeSerializerBase::Deserialize(Net::Stream& stream, ShapeType type) const
{
	if (CanBeProcessed(type)) return DeserializeImpl(stream);

	return GetNext()->Deserialize(stream, type);
}
//------------------------------------------------------------------------------
ShapeType ShapeSerializerBase::DeserializeType(Net::Stream& stream)
{
	return stream.ReadAs<uint8_t, ShapeType>();
}
//------------------------------------------------------------------------------
void ShapeSerializerBase::SerializeType(Net::Stream& stream, ShapeType type)
{
	stream.WriteAs<uint8_t>(type);
}
//------------------------------------------------------------------------------
}
