#include "SimpleShapeSeializer.h"

#include <ostream>
#include <sstream>
#include <iostream>

namespace wboard
{
//REGISTER_SERIALIZER(SimpleShapeSeializer);
//------------------------------------------------------------------------------
bool SimpleShapeSeializer::CanBeProcessed(ShapeType type) const
{
	return type == ShapeType::Circle
		|| type == ShapeType::Rect
		|| type == ShapeType::Line
		|| type == ShapeType::Curve;
}
//------------------------------------------------------------------------------
void SimpleShapeSeializer::SerializeImpl(std::stringstream& stream, const Shape& shape) const
{
	// TODO:: real serialization
	stream.write(reinterpret_cast<const char*>(shape.get()), sizeof(*shape));
}
//------------------------------------------------------------------------------
Shape SimpleShapeSeializer::DeserializeImpl(std::stringstream& stream) const
{
	// TODO:: real serialization
	auto shape = std::make_shared<SimpleShape>();

	std::cout << sizeof * shape << std::endl;
	stream.read(reinterpret_cast<char*>(shape.get()), sizeof(*shape));
	return shape;
}
//------------------------------------------------------------------------------	
}
