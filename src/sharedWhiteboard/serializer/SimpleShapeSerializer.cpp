#include "SimpleShapeSerializer.h"

#include "network/Stream.h"
#include <iostream>

namespace wboard
{
//REGISTER_SERIALIZER(SimpleShapeSeializer);
//------------------------------------------------------------------------------
bool SimpleShapeSerializer::CanBeProcessed(ShapeType type) const
{
	return type == ShapeType::Circle
		|| type == ShapeType::Rect
		|| type == ShapeType::Line
		|| type == ShapeType::Curve;
}
//------------------------------------------------------------------------------
void SimpleShapeSerializer::SerializeImpl(Net::Stream& stream, const Shape& shape) const
{
	// TODO:: real serialization
	stream.Write(shape.get(), sizeof(*shape));
}
//------------------------------------------------------------------------------
Shape SimpleShapeSerializer::DeserializeImpl(Net::Stream& stream) const
{
	// TODO:: real serialization
	auto shape = std::make_shared<SimpleShape>();

	std::cout << sizeof * shape << std::endl;
	stream.Read(reinterpret_cast<char*>(shape.get()), sizeof(*shape));
	return shape;
}
//------------------------------------------------------------------------------	
}
