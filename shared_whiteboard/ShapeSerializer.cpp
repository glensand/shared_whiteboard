#include "ShapeSerializer.h"

#include <typeinfo>

namespace wboard
{

Package ShapeSerializer::Serialize(const Shape& shape) const
{
	const auto& ser = GetSerializer(shape);

	return ser->Serialize(shape);
}

Shape ShapeSerializer::Deserialize(const Package& pcg) const
{
	const auto hash = *reinterpret_cast<size_t*>(pcg.RowData[0]);

	const auto& deserializer = m_serializers.at(hash);
	
	return deserializer->Deserialize(pcg);
}

ShapeSerializer& ShapeSerializer::Instance()
{
	static ShapeSerializer instance;

	return instance;
}

void ShapeSerializer::AddSerializer(size_t typeHash, SerializerInner&& serializer)
{
	m_serializers[typeHash] = std::move(serializer);
}

const SerializerInner& ShapeSerializer::GetSerializer(const Shape& shape) const
{
	const auto& typeInfo = typeid(shape.get());
	const auto hashCode = typeInfo.hash_code();

	const auto procIt = m_serializers.find(hashCode);

	// подумаем
	if (procIt == m_serializers.end());
		//return nullptr;

	return procIt->second;
}
	
}
