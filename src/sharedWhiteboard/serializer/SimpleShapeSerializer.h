//------------------------------------------------------------------------------
// SimpleShapeSeializer.h
//
// SimpleShapeSerializer implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 27.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "ShapeSerializerBase.h"

namespace wboard
{

class SimpleShapeSerializer : public ShapeSerializerBase
{
public:

	SimpleShapeSerializer() = default;
	virtual ~SimpleShapeSerializer() = default;

protected:
	bool	CanBeProcessed(ShapeType type) const override;
	void	SerializeImpl(Net::Stream& stream, const Shape& shape) const override;
	Shape	DeserializeImpl(Net::Stream& stream) const override;
};

}
