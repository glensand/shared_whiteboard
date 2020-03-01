
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

#include "ArgumentBase.h"
#include "sharedWhiteboard/Protocol/EArgumentType.h"
#include "whiteboard/render/ShapeData.h"

namespace wboard
{

// Еще один временный вонючий костыль
class InnerShape
{
public:

	explicit InnerShape(const Shape& simpleShape)
		: Shape(simpleShape)
	{
	}

	InnerShape() = default;
	
	void	SerializeTo(Net::Stream& stream) const;
	
	void	DeserializeFrom(Net::Stream& stream);

	Shape Shape;
};
	
class ArgumentShape : public ArgumentBase<InnerShape>
{
public:

	ArgumentShape(const Shape& value, const std::string& name)
		: ArgumentBase<InnerShape>(EArgumentType::Shape, name, InnerShape(value))
	{
	}

	ArgumentShape()
		:ArgumentBase<InnerShape>(EArgumentType::Shape){}

	virtual ~ArgumentShape() = default;
};
	
}

