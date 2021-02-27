/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include <cstdint>
#include <memory>

namespace wboard
{

enum class ShapeType
{
	Line,
	Circle,
	Rect,
	Curve
};
	
struct Color
{
	uint16_t	B{ 0 };
	uint16_t	G{ 0 };
	uint16_t	R{ 0 };
};

struct Point
{
	int		X{ 0 };
	int		Y{ 0 };
};
	
struct SimpleShape
{
	SimpleShape() = default;
	
	SimpleShape(ShapeType type)
		:Type(type)
	{}
	
	ShapeType	Type { ShapeType::Line };
	Color		ShapeColor;

	Point		P1;
	Point		P2;

	int			Thickness { 2 };
};

using Shape = std::shared_ptr<SimpleShape>;
	
}
