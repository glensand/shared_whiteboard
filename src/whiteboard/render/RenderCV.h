//------------------------------------------------------------------------------
// RenderCV.h
// 
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 02.08.2020
// Author: Gleb Bezborodov
//------------------------------------------------------------------------------
#pragma once

#include "RenderBase.h"
#include <opencv2/core/mat.hpp>

namespace wboard
{

struct ContextCV : RenderCtxBase
{
	virtual ~ContextCV() = default;

	cv::Mat			Board;
};
	
class RenderCV final : public RenderBase
{
public:
	RenderCV();
	virtual ~RenderCV() = default;
};
}

