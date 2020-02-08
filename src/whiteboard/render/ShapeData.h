//------------------------------------------------------------------------------
// ShapeData.h
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
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

using Data = std::unique_ptr<uint8_t>;
constexpr size_t MAX_PCG_SIZE{ 512 };
	
struct Package final
{
	size_t	Emount;
	uint8_t	RowData[MAX_PCG_SIZE];
};

using Shape = std::shared_ptr<SimpleShape>;
	
}
