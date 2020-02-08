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
#include "render/ShapeData.h"

namespace wboard
{

class ISerializerInner;
using Serializer = std::unique_ptr<ISerializerInner>;

class ISerializerInner
{
public:

	ISerializerInner() = default;
	virtual ~ISerializerInner() = default;

	virtual Package				Serialize(const Shape& shape) const = 0;
	virtual Shape				Deserialize(const Package& pcg) const = 0;
	
	virtual void				AddNext(Serializer&& ser) = 0;
	virtual const Serializer&	GetNext() = 0;
};
	
}

