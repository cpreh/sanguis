#include "hud.hpp"
#include <sge/font/text/part.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::scene::hud::hud(
	sge::font::metrics_ptr const _font_metrics,
	sge::font::text::drawer &_font_drawer
)
:
	font_metrics_(_font_metrics),
	font_drawer_(_font_drawer),
	experience_(0),
	level_(0),
	frames_counter_()
{
}

void
sanguis::client::draw2d::scene::hud::experience(
	client::exp const _experience
)
{
	experience_ = _experience;
}

void
sanguis::client::draw2d::scene::hud::level(
	client::level const _level
)
{
	level_ = _level;
}

void
sanguis::client::draw2d::scene::hud::update(
	time_type
)
{ 
	frames_counter_.update();

	sge::font::text::draw(
		font_metrics_,
		font_drawer_,
		sge::font::text::from_fcppt_string(
			(
				fcppt::format(
					FCPPT_TEXT("exp: %1%, level: %2%, fps: %3%")
				)
				% experience_
				% level_
				% frames_counter_.frames_str()
			).str()
		),
		sge::font::rect(
			sge::font::rect::vector::null(),
			sge::font::rect::dim(300, 100) // FIXME
		),
		sge::font::text::align_h::left,
		sge::font::text::align_v::top,
		sge::font::text::flags::none
	);
}
