﻿//------------------------------------------------------------------------------
// SimpleShapeSeializer.h
//
// SimpleShapeSeializer implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: dd.mm.2020
// Author: glensand
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
	void	SerializeImpl(std::ostream& stream, const Shape& shape) const override;
	Shape	DeserializeImpl(std::istream& stream) const override;
};

}