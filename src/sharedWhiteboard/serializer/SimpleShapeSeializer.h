//------------------------------------------------------------------------------
// SimpleShapeSeializer.h
//
// SimpleShapeSeializer implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: dd.mm.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "ShapeSerializerBase.h"

namespace wboard
{

class SimpleShapeSeializer : public ShapeSerializerBase
{
public:

	SimpleShapeSeializer() = default;
	virtual ~SimpleShapeSeializer() = default;

protected:
	bool	CanBeProcessed(ShapeType type) const override;
	void	SerializeImpl(std::stringstream& stream, const Shape& shape) const override;
	Shape	DeserializeImpl(std::stringstream& stream) const override;
};

}
