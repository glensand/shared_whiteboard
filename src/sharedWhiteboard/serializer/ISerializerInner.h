//------------------------------------------------------------------------------
// ISerializerInner.h
// Chain of responsibility 
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include <memory>

#include <whiteboard/render/ShapeData.h>

namespace wboard
{

class ISerializerInner;

using Serializer = std::unique_ptr<ISerializerInner>;

class ISerializerInner
{
public:

	ISerializerInner() = default;
	virtual ~ISerializerInner() = default;

	virtual void				Serialize(std::stringstream& stream, const Shape& shape) const = 0;
	virtual Shape				Deserialize(std::stringstream& stream) const = 0;
	
	virtual void				AddNext(Serializer&& ser) = 0;
	virtual const Serializer&	GetNext() const = 0;

	virtual Shape				Deserialize(std::stringstream& stream, ShapeType type) const = 0;
};
	
}

