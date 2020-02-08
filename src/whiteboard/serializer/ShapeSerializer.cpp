#include "ShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
Package ShapeSerializer::Serialize(const Shape& shape) const
{
	return m_serializerChain->Serialize(shape);
}

Shape ShapeSerializer::Deserialize(const Package& pcg) const
{
	return m_serializerChain->Deserialize(pcg);
}
//------------------------------------------------------------------------------
ShapeSerializer& ShapeSerializer::Instance()
{
	static ShapeSerializer instance;

	return instance;
}
//------------------------------------------------------------------------------
void ShapeSerializer::AddSerializer(Serializer&& serializer)
{
	auto next = std::move(m_serializerChain);
	m_serializerChain = std::move(serializer);

	m_serializerChain->AddNext(std::move(next));
}
//------------------------------------------------------------------------------
}
