/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <memory>

#include <whiteboard/render/ShapeData.h>

namespace Net
{
class Stream;
}

namespace wboard
{

class ISerializerInner;

using Serializer = std::unique_ptr<ISerializerInner>;

class ISerializerInner
{
public:

	ISerializerInner() = default;
	virtual ~ISerializerInner() = default;

	virtual void				Serialize(Net::Stream& stream, const Shape& shape) const = 0;
	virtual Shape				Deserialize(Net::Stream& stream) const = 0;
	
	virtual void				AddNext(Serializer&& ser) = 0;
	virtual const Serializer&	GetNext() const = 0;

	virtual Shape				Deserialize(Net::Stream& stream, ShapeType type) const = 0;
};
	
}

