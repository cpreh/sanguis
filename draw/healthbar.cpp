#include "healthbar.hpp"
#include "z_ordering.hpp"
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

sanguis::draw::sprite::unit const
	border_size = 2,
	bar_height = 8;

}

sanguis::draw::healthbar::healthbar(
	draw::environment const &env
)
:
	background(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_lower
		)
		.system(
			&env.colored_system()
		)
		.elements()
	),
	foreground(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_upper
		)
		.system(
			&env.colored_system()
		)
		.elements()
	),
	health_(0),
	max_health_(0)
{
	recalc_health();
}

void
sanguis::draw::healthbar::update_health(
	funit const nhealth,
	funit const nmax_health
)
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

void
sanguis::draw::healthbar::attach_to(
	sprite::point const &p,
	sprite::dim const &d
)
{
	pos(
		sprite::point(
			p.x(),
			p.y() - bar_height
		)
	);

	dim(
		sprite::dim(
			std::max(d.w(), 2 * border_size),
			bar_height
		)
	);
}

void
sanguis::draw::healthbar::pos(
	sprite::point const &pos_
)
{
	background.pos(
		pos_
	);

	inner.pos(
		inner_pos()
	);
}

void
sanguis::draw::healthbar::dim(
	sprite::dim const &dim_
)
{
	background.size(
		dim_
	);

	foreground.size(
		inner_dim()
	);

	recalc_health();
}

sanguis::draw::sprite::point const 
sanguis::draw::healthbar::inner_pos() const
{
	return
		background.pos()
		+ sprite::point(
			border_size,
			border_size
		);
}

sanguis::draw::sprite::dim const 
sanguis::draw::healthbar::inner_dim() const
{
	return
		border().size()
		- sprite::dim(
			2 * border_size,
			2 * border_size
		);
}

sanguis::draw::funit
sanguis::draw::healthbar::remaining_health() const
{
	return health_ / max_health_;
}

void
sanguis::draw::healthbar::recalc_health()
{
	if(health_ > max_health_)
		return;

	if(sge::math::almost_zero(max_health_)) // TODO:
		return;
	
	foreground.w(
		static_cast<
			sprite::unit
		>(
			static_cast<
				funit
			>(
				inner_dim().w()
			)
			* remaining_health()
		)
	);

	sge::image::color::channel8 const pixel_channel_max(
		sprite::colored::color_format::channel_max<
			mizuiro::color::channel::alpha
		>()
	);

	foreground.color(
		sprite::colored::color(
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
