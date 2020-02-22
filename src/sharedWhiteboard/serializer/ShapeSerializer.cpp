#include "ShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
void ShapeSerializer::Serialize(std::ostream& stream, const Shape& shape) const
{
	m_serializerChain->Serialize(stream, shape);
}

Shape ShapeSerializer::Deserialize(std::istream& stream) const
{
	return m_serializerChain->Deserialize(stream);
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
