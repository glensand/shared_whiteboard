
//------------------------------------------------------------------------------
// ArgumentShape.h
//
// ArgumentShape implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: 28.02.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include "IArgument.h"
#include "whiteboard/render/ShapeData.h"

namespace wboard
{
	
class ArgumentShape : public IArgument
{
public:

	ArgumentShape(Shape&& shape);
	
	virtual ~ArgumentShape() = default;

	void	SerializeTo(Net::Stream& stream) const override;
	
	void	DeserializeFrom(Net::Stream& stream) override;

private:
	Shape	m_shape;
};
	
}

