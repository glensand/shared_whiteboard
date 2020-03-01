#include "ArgumentShape.h"

#include "sharedWhiteboard/serializer/ShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
void InnerShape::SerializeTo(Net::Stream& stream) const
{
	// Это два вонючих костыля
// надо бы убрать и сделать нормально
	ShapeSerializer::Instance().Serialize(stream, Shape);
}
//------------------------------------------------------------------------------
void InnerShape::DeserializeFrom(Net::Stream& stream)
{
	Shape = ShapeSerializer::Instance().Deserialize(stream);
}
//------------------------------------------------------------------------------
}
