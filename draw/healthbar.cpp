#include "healthbar.hpp"
#include "z_ordering.hpp"
#include "../client/id_dont_care.hpp"
#include <sge/su.hpp>
#include <sge/format.hpp>
#include <sge/math/compare.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>
#include <boost/none.hpp>
#include <limits>

namespace
{

const sge::sprite::unit border_size = 2,
                        bar_height = 8;

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
	at(0) = object(
		sys,
		z_ordering::healthbar_lower,
		boost::none,
		boost::none,
		boost::none,
		sge::renderer::colors::black);

	at(1) = object(
		sys,
		z_ordering::healthbar_upper);/*,
		boost::none,
		boost::none,
		boost::none,
		boost::none,
		static_cast<sge::sprite::rotation_type>(0));*/

	recalc_health();
}

void sanguis::draw::healthbar::health(
	const sge::space_unit nhealth)
{
	health_ = nhealth;
	recalc_health();
}

void sanguis::draw::healthbar::max_health(
	const sge::space_unit nmax_health)
{
	max_health_ = nmax_health;
	recalc_health();
}

sge::space_unit
sanguis::draw::healthbar::health() const
{
	return health_;
}

sge::space_unit
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
			d.w(),
			bar_height));
}

bool sanguis::draw::healthbar::dead() const
{
	return health() <= 0;
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
	return at(0);
}

const sanguis::draw::object&
sanguis::draw::healthbar::border() const
{
	return at(0);
}

sanguis::draw::object&
sanguis::draw::healthbar::inner()
{
	return at(1);
}

const sanguis::draw::object&
sanguis::draw::healthbar::inner() const
{
	return at(1);
}

sge::space_unit
sanguis::draw::healthbar::remaining_health() const
{
	return health_ / max_health_;
}

void sanguis::draw::healthbar::recalc_health()
{
	if(health_ > max_health_)
		throw sge::exception(
			(sge::format(SGE_TEXT("draw::healthbar: health (%1%) > max_health (%2%)!"))
			% health_
			% max_health_).str());

	if(dead())
	{
		visible(false);
		return;
	}
	visible(true);

	if(sge::math::almost_zero(max_health_)) // TODO:
		return;
	
	const sge::renderer::pixel_channel_8 pixel_channel_max(
		std::numeric_limits<sge::renderer::pixel_channel_8>::max());

	inner().w() = static_cast<sge::sprite::unit>(
		static_cast<sge::space_unit>(inner_dim().w()) * remaining_health());
	inner().set_color(sge::renderer::make_color_rgba(
		static_cast<sge::renderer::pixel_channel_8>(
			(sge::su(1) - remaining_health()) * sge::su(pixel_channel_max)),
		static_cast<sge::renderer::pixel_channel_8>(
			remaining_health() * sge::su(pixel_channel_max)),
		0,
		pixel_channel_max));
}
