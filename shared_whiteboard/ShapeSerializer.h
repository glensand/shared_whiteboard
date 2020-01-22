#pragma once

#include <unordered_map>
#include "ISerializerInner.h"

// Это будет синглтон для фабрики
// все конструкторы я укажу явно
namespace wboard
{

class ShapeSerializer final
{
public:

	// Поудаляли то что не нужно и не должно быть использовано
	ShapeSerializer(ShapeSerializer&&) = delete;
	ShapeSerializer(ShapeSerializer&) = delete;

	ShapeSerializer operator=(ShapeSerializer&) = delete;
	ShapeSerializer operator=(ShapeSerializer&&) = delete;
	
	~ShapeSerializer() = default;

	Package						Serialize(const Shape& shape) const;
	Shape						Deserialize(const Package& pcg) const;
	
	static ShapeSerializer&		Instance();
	void						AddSerializer(ShapeType typeHash, SerializerInner&& serializer);

	
private:
	const SerializerInner&		GetSerializer(const Shape& shape) const;
	
	ShapeSerializer() = default;

	// Я обьясню наверное как это работает, а может и нет))
	std::unordered_map<ShapeType, SerializerInner>	m_serializers;
};

template <typename S>
struct SerializerRegister
{
	SerializerRegister(ShapeType type)
	{
		SerializerInner processor(reinterpret_cast<ISerializerInner*>(new S));

		ShapeSerializer::Instance().AddSerializer(type, std::move(processor));
	}
};

#define REGISTER_SERIALIZER(shapeType, serializerName) static SerializerRegister<serializerName> \
	registernewRegister##serializerName(shapeType)
	
}
