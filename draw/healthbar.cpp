#include "healthbar.hpp"
#include "z_ordering.hpp"
#include "../client/id_dont_care.hpp"
#include <sge/su.hpp>
#include <sge/format.hpp>
#include <sge/math/compare.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>
#include <boost/none.hpp>

namespace
{

const sge::sprite::unit border_size = 2,
                        bar_height = 8;

}

sanguis::draw::healthbar::healthbar()
: sprite(
	client::id_dont_care(),
	2),
  health_(0),
  max_health_(0)
{
	at(0) = sge::sprite::object(
		boost::none,
		boost::none,
		boost::none,
		sge::colors::darkgrey,
		z_ordering::healthbar_lower,
		static_cast<sge::sprite::rotation_type>(0)),

	at(1) = sge::sprite::object(
		boost::none,
		boost::none,
		boost::none,
		boost::none,
		z_ordering::healthbar_upper,
		static_cast<sge::sprite::rotation_type>(0));

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
	return border().size() - sge::sprite::dim(border_size, border_size);
}

sge::sprite::object&
sanguis::draw::healthbar::border()
{
	return at(0);
}

const sge::sprite::object&
sanguis::draw::healthbar::border() const
{
	return at(0);
}

sge::sprite::object&
sanguis::draw::healthbar::inner()
{
	return at(1);
}

const sge::sprite::object&
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

	if(sge::math::almost_zero(max_health_)) // TODO:
		return;
	
	inner().w() = static_cast<sge::sprite::unit>(
		static_cast<sge::space_unit>(inner_dim().w()) * remaining_health());
	inner().set_color(sge::make_color(
		static_cast<sge::color_element>(
			(sge::su(1) - remaining_health()) * sge::color_element_max),
		static_cast<sge::color_element>(
			remaining_health() * sge::color_element_max),
		0,
		sge::color_element_max));
}
