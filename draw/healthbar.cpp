#include "healthbar.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "../client/id_dont_care.hpp"
#include "../exception.hpp"
#include <sge/format.hpp>
#include <sge/math/compare.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>
#include <boost/none.hpp>
#include <algorithm>
#include <limits>

namespace
{

sge::sprite::unit const
	border_size = 2,
	bar_height = 8;

sanguis::draw::sprite_part_index const
	background(0),
	foreground(1);

}

sanguis::draw::healthbar::healthbar(
	system &sys)
: sprite(
	client::id_dont_care(),
	sys,
	2,
	z_ordering::model_generic),
  health_(0),
  max_health_(0)
{
	at(background) = object(
		sys,
		z_ordering::healthbar_lower,
		boost::none,
		boost::none,
		boost::none,
		sge::renderer::colors::black());

	at(foreground) = object(
		sys,
		z_ordering::healthbar_upper);

	recalc_health();
}

void sanguis::draw::healthbar::health(
	const funit nhealth)
{
	health_ = nhealth;
	recalc_health();
}

void sanguis::draw::healthbar::max_health(
	const funit nmax_health)
{
	max_health_ = nmax_health;
	recalc_health();
}

sanguis::draw::funit
sanguis::draw::healthbar::health() const
{
	return health_;
}

sanguis::draw::funit
sanguis::draw::healthbar::max_health() const
{
	return max_health_;
}

void sanguis::draw::healthbar::attach_to(
	const sge::sprite::point& p,
	const sge::sprite::dim& d)
{
	pos(
		sge::sprite::point(
			p.x(),
			p.y() - bar_height));
	dim(
		sge::sprite::dim(
			std::max(d.w(), 2 * border_size),
			bar_height));
}

void sanguis::draw::healthbar::pos(
	const sge::sprite::point& p)
{
	border().pos() = p;
	inner().pos() = inner_pos();
}

void sanguis::draw::healthbar::dim(
	const sge::sprite::dim& d)
{
	border().size() = d;
	inner().size() = inner_dim();
	recalc_health();
}

const sge::sprite::point
sanguis::draw::healthbar::inner_pos() const
{
	return border().pos() + sge::sprite::point(border_size, border_size);
}

const sge::sprite::dim
sanguis::draw::healthbar::inner_dim() const
{
	return border().size() - sge::sprite::dim(2 * border_size, 2 * border_size);
}

sanguis::draw::object&
sanguis::draw::healthbar::border()
{
	return at(background);
}

const sanguis::draw::object&
sanguis::draw::healthbar::border() const
{
	return at(background);
}

sanguis::draw::object&
sanguis::draw::healthbar::inner()
{
	return at(foreground);
}

const sanguis::draw::object&
sanguis::draw::healthbar::inner() const
{
	return at(foreground);
}

sanguis::draw::funit
sanguis::draw::healthbar::remaining_health() const
{
	return health_ / max_health_;
}

void sanguis::draw::healthbar::recalc_health()
{
	if(health_ > max_health_)
		throw exception(
			(sge::format(SGE_TEXT("draw::healthbar: health (%1%) > max_health (%2%)!"))
			% health_
			% max_health_).str());

	if(sge::math::almost_zero(max_health_)) // TODO:
		return;
	
	sge::renderer::color_channel_8 const pixel_channel_max(
		std::numeric_limits<sge::renderer::color_channel_8>::max());

	inner().w() = static_cast<sge::sprite::unit>(
		static_cast<funit>(inner_dim().w()) * remaining_health());
	inner().color(sge::renderer::rgba8_color(
		static_cast<sge::renderer::color_channel_8>(
			(static_cast<funit>(1) - remaining_health()) * static_cast<funit>(pixel_channel_max)),
		static_cast<sge::renderer::color_channel_8>(
			remaining_health() * static_cast<funit>(pixel_channel_max)),
		0,
		pixel_channel_max));
}
