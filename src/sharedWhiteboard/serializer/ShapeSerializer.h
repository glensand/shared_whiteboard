//------------------------------------------------------------------------------
// ShapeSerializer.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include "ISerializerInner.h"

namespace wboard
{

class ShapeSerializer final
{
public:
	ShapeSerializer(ShapeSerializer&&) = delete;
	ShapeSerializer(ShapeSerializer&) = delete;

	ShapeSerializer operator=(ShapeSerializer&) = delete;
	ShapeSerializer operator=(ShapeSerializer&&) = delete;
	
	~ShapeSerializer() = default;

	void						Serialize(std::ostream& stream, const Shape& shape) const;
	Shape						Deserialize(std::istream& stream) const;
	
	static ShapeSerializer&		Instance();
	void						AddSerializer(Serializer&& serializer);
	
private:
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
