#include "Serializers.h"
#include "ShapeSerializer.h"
#include "ShapeData.h"

namespace wboard
{
	
REGISTER_SERIALIZER(Line, LineSerializer);
REGISTER_SERIALIZER(Rect, RectSerializer);
REGISTER_SERIALIZER(Circle, CircleSerializer);
REGISTER_SERIALIZER(Text, TextSerializer);

size_t SerializerBase::GetHashCode(const Shape& shape)
{
	const auto& typeInfo = typeid(shape.get());
	const auto hashCode = typeInfo.hash_code();
	
	return hashCode;
}

Package LineSerializer::Serialize(const Shape& shape) const
{
	return SerializeBase<Line>(shape);
}

Shape LineSerializer::Deserialize(const Package& pcg) const
{
	return DeserializeBase<Line>(pcg);
}

Package CircleSerializer::Serialize(const Shape& shape) const
{
	return SerializeBase<Circle>(shape);
}

Shape CircleSerializer::Deserialize(const Package& pcg) const
{
	return DeserializeBase<Circle>(pcg);
}

Package RectSerializer::Serialize(const Shape& shape) const
{
	return SerializeBase<Rect>(shape);
}

Shape RectSerializer::Deserialize(const Package& pcg) const
{
	return DeserializeBase<Rect>(pcg);
}

Package TextSerializer::Serialize(const Shape& shape) const
{
	return SerializeBase<Text>(shape);
}

Shape TextSerializer::Deserialize(const Package& pcg) const
{
	return DeserializeBase<Text>(pcg);
}
	
}
