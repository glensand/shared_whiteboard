/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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

