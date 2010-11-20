#include "hud.hpp"
#include <sge/font/text/part.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/flags_none.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::scene::hud::hud(
	sge::font::metrics_ptr const _font_metrics,
	sge::font::text::drawer_ptr const _font_drawer
)
:
	font_metrics_(_font_metrics),
	font_drawer_(_font_drawer),
	experience_(0),
	level_(0)
{}

void
sanguis::client::draw2d::scene::hud::experience(
	exp_type const nexperience
)
{
	experience_ = nexperience;
}

void
sanguis::client::draw2d::scene::hud::level(
	level_type const nlevel
)
{
	level_ = nlevel;
}

void
sanguis::client::draw2d::scene::hud::update(
	time_type
)
{ 
	frames_counter.update();

	sge::font::text::draw(
		font_metrics_,
		font_drawer_,
		(
			fcppt::format(
				FCPPT_TEXT("exp: %1%, level: %2%, fps: %3%")
			)
			% experience_
			% level_
			% frames_counter.frames_str()
		).str(),
		sge::font::pos::null(),
		sge::font::dim(300, 100), // FIXME
		sge::font::text::align_h::left,
		sge::font::text::align_v::top,
		sge::font::text::flags::none
	);
}
