#include "healthbar.hpp"
#include "resource_factory.hpp"
#include "z_ordering.hpp"
#include <sge/renderer/color.hpp>

namespace
{

const sge::sprite::unit border_size = 2;

}

sanguis::draw::healthbar::healthbar(
	const entity_id id,
	const sge::sprite::point& pos,
	const sge::sprite::dim& dim,
	const sge::space_unit health_,
	const sge::space_unit max_health_)
: sprite(
	id,
	sge::math::vector2(0,0),
	sge::sprite::object(
		pos,
		resource::texture(SGE_TEXT("healthbar_border")),
		dim,
		sge::colors::white,
		z_ordering::healthbar_lower,
		static_cast<sge::sprite::rotation_type>(0))),
  health_(health_),
  max_health_(max_health_)
{
	add_sprite(
		sge::sprite::object(
			inner_pos(),
			sge::virtual_texture_ptr(),
			inner_dim(),
			sge::colors::green,
			z_ordering::healthbar_upper,
			static_cast<sge::sprite::rotation_type>(0)));
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
	return max_health_ - health_;
}

void sanguis::draw::healthbar::recalc_health()
{
	inner().w() = static_cast<sge::sprite::unit>(
		static_cast<sge::space_unit>(inner_dim().w()) * remaining_health());
	inner().set_color(sge::make_color(
		static_cast<sge::color_element>((sge::su(1) - remaining_health()) * sge::color_element_max),
		static_cast<sge::color_element>(remaining_health() * sge::color_element_max),
		0,
		sge::color_element_max));
}
