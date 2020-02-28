#include "ShapeSerializer.h"

#include "SimpleShapeSerializer.h"

namespace wboard
{
//------------------------------------------------------------------------------
void ShapeSerializer::Serialize(Net::Stream& stream, const Shape& shape) const
{
	m_serializerChain->Serialize(stream, shape);
}
//------------------------------------------------------------------------------
Shape ShapeSerializer::Deserialize(Net::Stream& stream) const
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
ShapeSerializer::ShapeSerializer()
{
	AddSerializer(std::unique_ptr<ISerializerInner>(std::make_unique<SimpleShapeSerializer>()));
}
//------------------------------------------------------------------------------
}
