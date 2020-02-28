#include "ArgumentShape.h"

#include "sharedWhiteboard/serializer/ShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
ArgumentShape::ArgumentShape(Shape&& shape)
	: m_shape(std::move(shape))
{
}
//------------------------------------------------------------------------------
void ArgumentShape::SerializeTo(Net::Stream& stream) const
{
	// Это два вонючих костыля
	// надо бы убрать и сделать нормально
	ShapeSerializer::Instance().Serialize(stream, shape);
}
//------------------------------------------------------------------------------
void ArgumentShape::DeserializeFrom(Net::Stream& stream)
{
	m_shape = ShapeSerializer::Instance().Deserialize(stream);
}
//------------------------------------------------------------------------------
}
