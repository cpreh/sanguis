#include "hud.hpp"
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::scene::hud::hud(
	sge::font::object &font
)
:
	font(font),
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

	font.draw_text(
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
		sge::font::align_h::left,
		sge::font::align_v::top
	);
}
