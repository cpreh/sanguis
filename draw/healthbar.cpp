#include "healthbar.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "object.hpp"
#include "../client/id_dont_care.hpp"
#include "../exception.hpp"
#include <sge/format.hpp>
#include <sge/math/almost_zero.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/colors.hpp>
#include <sge/sprite/intrusive/parameters.hpp>
#include <boost/none.hpp>
#include <algorithm>

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
	draw::environment const &env)
:
	sprite(
		env,
		client::id_dont_care(),
		2,
		z_ordering::model_generic),
	health_(0),
	max_health_(0)
{
	at(background) = object(
		sge::sprite::intrusive::parameters(
			system(),
			z_ordering::healthbar_lower
		)
		.color(
			sge::image::colors::black()
		)
	);

	at(foreground) = object(
		sge::sprite::intrusive::parameters(
			system(),
			z_ordering::healthbar_upper
		)
	);

	recalc_health();
}

void sanguis::draw::healthbar::update_health(
	funit const nhealth,
	funit const nmax_health)
{
	health_ = nhealth;
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
	sge::sprite::point const &p,
	sge::sprite::dim const &d)
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
	sge::sprite::point const &p)
{
	border().pos() = p;
	inner().pos() = inner_pos();
}

void sanguis::draw::healthbar::dim(
	sge::sprite::dim const &d)
{
	border().size() = d;
	inner().size() = inner_dim();
	recalc_health();
}

sge::sprite::point const 
sanguis::draw::healthbar::inner_pos() const
{
	return border().pos() + sge::sprite::point(border_size, border_size);
}

sge::sprite::dim const 
sanguis::draw::healthbar::inner_dim() const
{
	return border().size() - sge::sprite::dim(2 * border_size, 2 * border_size);
}

sanguis::draw::object &
sanguis::draw::healthbar::border()
{
	return at(background);
}

sanguis::draw::object const &
sanguis::draw::healthbar::border() const
{
	return at(background);
}

sanguis::draw::object&
sanguis::draw::healthbar::inner()
{
	return at(foreground);
}

sanguis::draw::object const &
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
		return;
		/*
		throw exception(
			(sge::format(SGE_TEXT("draw::healthbar: health (%1%) > max_health (%2%)!"))
			% health_
			% max_health_).str()
		);
		*/

	if(sge::math::almost_zero(max_health_)) // TODO:
		return;
	
	inner().w() = static_cast<sge::sprite::unit>(
		static_cast<
			funit
		>(
			inner_dim().w()
		) * remaining_health()
	);

	sge::image::color::channel8 const pixel_channel_max(
		sge::image::color::rgba8::format::channel_max<
			mizuiro::color::channel::alpha
		>()
	);

	inner().color(
		sge::image::color::rgba8(
			sge::image::color::init::red =
			static_cast<
				sge::image::color::channel8
			>(
				(static_cast<funit>(1) - remaining_health())
				* static_cast<funit>(pixel_channel_max)
			),
			sge::image::color::init::green =
			static_cast<
				sge::image::color::channel8
			>(
				remaining_health() * static_cast<funit>(pixel_channel_max)
			),
			sge::image::color::init::blue %= 0.0,
			sge::image::color::init::alpha %= 1.0
		)
	);
}
