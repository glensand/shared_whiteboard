#include "ShapeSerializer.h"

namespace wboard
{

Package ShapeSerializer::Serialize(const Shape& shape) const
{
	const auto& ser = GetSerializer(shape);

	return ser->Serialize(shape);
}

Shape ShapeSerializer::Deserialize(const Package& pcg) const
{
	const auto hash = *reinterpret_cast<ShapeType*>(pcg.RowData[0]);

	const auto& deserializer = m_serializers.at(hash);
	
	return deserializer->Deserialize(pcg);
}

ShapeSerializer& ShapeSerializer::Instance()
{
	static ShapeSerializer instance;

	return instance;
}

void ShapeSerializer::AddSerializer(ShapeType typeHash, SerializerInner&& serializer)
{
	m_serializers[typeHash] = std::move(serializer);
}

const SerializerInner& ShapeSerializer::GetSerializer(const Shape& shape) const
{
	const auto procIt = m_serializers.find(shape->Type);

	// подумаем
	if (procIt == m_serializers.end());
		//return nullptr;

	return procIt->second;
}
	
}
