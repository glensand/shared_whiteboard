/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <unordered_map>
#include "ISerializerInner.h"

namespace Net
{
class Stream;
}

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

	void						Serialize(Net::Stream& stream, const Shape& shape) const;
	Shape						Deserialize(Net::Stream& stream) const;
	
	static ShapeSerializer&		Instance();
	void						AddSerializer(Serializer&& serializer);
	
private:
	ShapeSerializer();

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
