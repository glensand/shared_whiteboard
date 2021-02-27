/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

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
