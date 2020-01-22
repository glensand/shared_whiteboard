#include "RenderCV.h"

#include <opencv2/imgproc/imgproc_c.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace wboard
{
// Это рендереры, щас напихаю сюда побольше!

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
		const auto line = reinterpret_cast<const Line*>(shape.get());

		cv::line(ctx.Board, Point2cvPoint(line->P1), Point2cvPoint(line->P2),
			CvColor(line->ShapeColor), line->Thickness, CV_AA);
	}
};

struct RenderCirce final : RenderCVBase
{
	void RenderImpl(const Shape& shape, const ContextCV& ctx) const override
	{
		const auto circle = reinterpret_cast<const Circle*>(shape.get());
		
		//cv::circle(ctx.Board, Point2cvPoint(circle->Center), circle->Rad, 
		//	CvColor(circle->ShapeColor), circle->Rad);
	}
};
	
RenderCV::RenderCV()
{
	Initialize(ShapeType::Circle, std::make_unique<RenderCirce>());
	Initialize(ShapeType::Line, std::make_unique<RenderLine>());
}
	
}
