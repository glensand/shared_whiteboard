#include "Serializers.h"
#include "ShapeSerializer.h"
#include "ShapeData.h"

namespace wboard
{
	
Package SerializerBase::Serialize(const Shape& shape) const
{
	const auto type = shape->Type;
	if (CanBeProcessed(type)) return SerializeImpl(shape);
	
	return m_next->Serialize(shape);
}

Shape SerializerBase::Deserialize(const Package& pcg) const
{
	const auto begin = reinterpret_cast<const size_t*>(pcg.RowData);
	const auto type = *reinterpret_cast<const ShapeType*>(begin + 1);
	
	if (CanBeProcessed(type)) return DeserializeImpl(pcg);

	return m_next->Deserialize(pcg);
}

void SerializerBase::AddNext(Serializer&& ser)
{
	m_next = std::move(ser);
}

const Serializer& SerializerBase::GetNext()
{
	return m_next;
}

class SimpleShapeSerializer final : public SerializerBase
{
	
protected:
	Package SerializeImpl(const Shape& shape) const override;
	Shape	DeserializeImpl(const Package& pcg) const override;

	bool	CanBeProcessed(ShapeType type) const override;
};

Package SimpleShapeSerializer::SerializeImpl(const Shape& shape) const
{
	return SerializeBase<SimpleShape>(shape);
}

Shape SimpleShapeSerializer::DeserializeImpl(const Package& pcg) const
{
	return DeserializeBase<SimpleShape>(pcg);
}

bool SimpleShapeSerializer::CanBeProcessed(ShapeType type) const
{
	return type == ShapeType::Circle
		|| type == ShapeType::Rect
		|| type == ShapeType::Line;
}

REGISTER_SERIALIZER(SimpleShapeSerializer);

}
