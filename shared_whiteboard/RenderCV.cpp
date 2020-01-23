#include "RenderCV.h"

#include <opencv2/imgproc/imgproc_c.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace wboard
{

struct RenderCVBase : IRenderInner
{
	void Render(const RenderCtx& ctx) const final
	{
		const auto cvCtx = dynamic_cast<const ContextCV*>(ctx.get());

		if (cvCtx == nullptr) return;

		RenderImpl(ctx->Shape, *cvCtx);
	}

	static cv::Point Point2cvPoint(const Point& p)
	{
		return cvPoint(p.X, p.Y);
	}

	static cv::Scalar CvColor(const Color& col)
	{
		return cv::Scalar(col.B, col.G, col.R);
	}
	
	virtual void RenderImpl(const Shape& shape, const ContextCV& ctx) const = 0;
};
	
struct RenderLine final : RenderCVBase
{
	void RenderImpl(const Shape& shape, const ContextCV& ctx) const override
	{
		cv::line(ctx.Board, Point2cvPoint(shape->P1), Point2cvPoint(shape->P2),
			CvColor(shape->ShapeColor), shape->Thickness, CV_AA);
	}
};

struct RenderCirce final : RenderCVBase
{
	void RenderImpl(const Shape& shape, const ContextCV& ctx) const override
	{
		const auto distX = (shape->P1.X - shape->P2.X);
		const auto distY = (shape->P1.Y - shape->P2.Y);
		
		const auto rad = std::sqrt(distX * distX + distY * distY);

		cv::circle(ctx.Board, Point2cvPoint(shape->P1), rad, 
			CvColor(shape->ShapeColor), shape->Thickness);
	}
};
	
RenderCV::RenderCV()
{
	Initialize(ShapeType::Circle, std::make_unique<RenderCirce>());
	Initialize(ShapeType::Line, std::make_unique<RenderLine>());
}
	
}
