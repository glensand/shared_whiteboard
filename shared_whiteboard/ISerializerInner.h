#pragma once
#include "ShapeData.h"

// Это конкретные сериализаторы
// по одному на каждую фигуру

namespace wboard
{

class ISerializerInner;
using Serializer = std::unique_ptr<ISerializerInner>;

class ISerializerInner
{
public:

	ISerializerInner() = default;
	virtual ~ISerializerInner() = default;

	virtual Package	Serialize(const Shape& shape) const = 0;
	virtual Shape	Deserialize(const Package& pcg) const = 0;
	
	virtual void					AddNext(Serializer&& ser) = 0;
	virtual const Serializer&		GetNext() = 0;
};
	
}

