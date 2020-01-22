#pragma once

#include <string>
#include <unordered_map>
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

