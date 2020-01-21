#pragma once

#include "ISerializerInner.h"

// Здесь жахнем сериализаторов...

namespace wboard
{

	// Здесь надо натыкать деструкторов, но мне лень

class SerializerBase : public ISerializerInner
{
protected:
	template<typename T>
	static Shape	DeserializeBase(const Package& pcg);

	template<typename T>
	static Package	SerializeBase(const Shape& shape);

private:
	static size_t	GetHashCode(const Shape& shape);
};

template <typename T>
Shape SerializerBase::DeserializeBase(const Package& pcg)
{
	Shape shape = std::make_unique<Line>();
	auto* rowShape = shape.get();
	const auto* pcgData = reinterpret_cast<const uint8_t*>(pcg.RowData);
	const auto* begin = pcgData + sizeof(size_t);

	std::copy(begin, begin + pcg.Emount - sizeof(size_t), rowShape);

	return shape;
}

template <typename T>
Package SerializerBase::SerializeBase(const Shape& shape)
{
	Package pcg{};

	pcg.Emount = sizeof(T) + sizeof(size_t);
	const auto* begin = reinterpret_cast<const uint8_t*>(shape.get());

	const auto data = reinterpret_cast<size_t*>(pcg.RowData);
	*data = GetHashCode(shape);

	std::copy(begin, begin + pcg.Emount, data + 1);

	return pcg;
}
	
class LineSerializer final : public SerializerBase
{
public:
	Package Serialize(const Shape& shape) const override;
	Shape	Deserialize(const Package& pcg) const override;
};

class RectSerializer final : public SerializerBase
{
public:
	Package Serialize(const Shape& shape) const override;
	Shape	Deserialize(const Package& pcg) const override;
};

class TextSerializer final : public SerializerBase
{
public:
	Package Serialize(const Shape& shape) const override;
	Shape	Deserialize(const Package& pcg) const override;
};

class CircleSerializer final : public SerializerBase
{
public:
	Package Serialize(const Shape& shape) const override;
	Shape	Deserialize(const Package& pcg) const override;
};
	
}
