#include "hud.hpp"
#include <sge/font/object.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/format.hpp>
#include <sge/text.hpp>

sanguis::draw::hud::hud(
	sge::font::object &font)
:
	font(font),
	experience_(0),
	level_(0)
{}

void sanguis::draw::hud::experience(
	messages::exp_type const nexperience)
{
	experience_ = nexperience;
}

void sanguis::draw::hud::level(
	messages::level_type const nlevel)
{
	level_ = nlevel;
}

void sanguis::draw::hud::update(
	time_type)
{ 
	frames_counter.update();

	font.draw_text((
		sge::format(
			SGE_TEXT("exp: %1%, level: %2%, fps: %3%"))
			% experience_
			% level_
			% frames_counter.frames_str())
			.str(),
		sge::font::pos::null(),
		sge::font::dim(200, 100), // FIXME
		sge::font::align_h::left,
		sge::font::align_v::top);
}
