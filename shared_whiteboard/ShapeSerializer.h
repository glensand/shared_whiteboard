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
	void						AddSerializer(Serializer&& serializer);
	
private:
	const Serializer&		GetSerializer(const Shape& shape) const;
	
	ShapeSerializer() = default;

						// I suppose chain of responsibility, it is most appropriate method
						// to abstract serialization now
	Serializer		m_serializerChain;
};

template <typename S>
struct SerializerRegister
{
	SerializerRegister()
	{
		Serializer processor(reinterpret_cast<ISerializerInner*>(new S));

		ShapeSerializer::Instance().AddSerializer(std::move(processor));
	}
};

#define REGISTER_SERIALIZER(serializerName) static SerializerRegister<serializerName> \
	registernewRegister##serializerName
	
}
