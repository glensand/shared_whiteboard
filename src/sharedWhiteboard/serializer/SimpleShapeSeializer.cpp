#include "SimpleShapeSeializer.h"

#include <ostream>
#include <istream>

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
void SimpleShapeSeializer::SerializeImpl(std::ostream& stream, const Shape& shape) const
{
	// TODO:: real serialization
	stream.write(reinterpret_cast<const char*>(shape.get()), sizeof(*shape));
}
//------------------------------------------------------------------------------
Shape SimpleShapeSeializer::DeserializeImpl(std::istream& stream) const
{
	// TODO:: real serialization
	auto shape = std::make_shared<SimpleShape>();
	stream.read(reinterpret_cast<char*>(shape.get()), sizeof(*shape));
	return shape;
}
//------------------------------------------------------------------------------	
}
