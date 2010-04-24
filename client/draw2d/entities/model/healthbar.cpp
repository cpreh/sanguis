#include "healthbar.hpp"
#include "../../z_ordering.hpp"
#include "../../sprite/colored/parameters.hpp"
#include "../../sprite/colored/color.hpp"
#include "../../sprite/colored/color_format.hpp"
#include "../../sprite/unit.hpp"
#include "../../../id_dont_care.hpp"
#include "../../../../exception.hpp"
#include <fcppt/format.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/colors.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <mizuiro/color/types/channel_value.hpp>
#include <mizuiro/color/channel_max.hpp>
#include <algorithm>

namespace
{

sanguis::client::draw2d::sprite::unit const
	border_size = 2,
	bar_height = 8;

}

sanguis::client::draw2d::entities::model::healthbar::healthbar(
	sprite::colored::system &sys
)
:
	background(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_lower
		)
		.system(
			&sys
		)
		.color(
			sge::image::color::any::convert<
				sprite::colored::color_format	
			>(
				sge::image::colors::black()
			)
		)
		.elements()
	),
	foreground(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_upper
		)
		.system(
			&sys
		)
		.elements()
	),
	health_(0),
	max_health_(0)
{
	recalc_health();
}

sanguis::client::draw2d::entities::model::healthbar::~healthbar()
{}

void
sanguis::client::draw2d::entities::model::healthbar::update_health(
	health_type const nhealth,
	health_type const nmax_health
)
{
	health_ = nhealth;
	max_health_ = nmax_health;

	recalc_health();
}

sanguis::client::health_type
sanguis::client::draw2d::entities::model::healthbar::health() const
{
	return health_;
}

sanguis::client::health_type
sanguis::client::draw2d::entities::model::healthbar::max_health() const
{
	return max_health_;
}

void
sanguis::client::draw2d::entities::model::healthbar::attach_to(
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
sanguis::client::draw2d::entities::model::healthbar::pos(
	sprite::point const &pos_
)
{
	background.pos(
		pos_
	);

	foreground.pos(
		inner_pos()
	);
}

void
sanguis::client::draw2d::entities::model::healthbar::dim(
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

sanguis::client::draw2d::sprite::point const 
sanguis::client::draw2d::entities::model::healthbar::inner_pos() const
{
	return
		background.pos()
		+ sprite::point(
			border_size,
			border_size
		);
}

sanguis::client::draw2d::sprite::dim const 
sanguis::client::draw2d::entities::model::healthbar::inner_dim() const
{
	return
		background.size()
		- sprite::dim(
			2 * border_size,
			2 * border_size
		);
}

sanguis::client::health_type
sanguis::client::draw2d::entities::model::healthbar::remaining_health() const
{
	return health_ / max_health_;
}

void
sanguis::client::draw2d::entities::model::healthbar::recalc_health()
{
	if(health_ > max_health_)
		return;

	if(fcppt::math::almost_zero(max_health_)) // TODO:
		return;
	
	foreground.w(
		static_cast<
			sprite::unit
		>(
			static_cast<
				health_type
			>(
				inner_dim().w()
			)
			* remaining_health()
		)
	);

	typedef mizuiro::color::types::channel_value<
		sprite::colored::color_format,
		mizuiro::color::channel::alpha
	>::type alpha_value;

	alpha_value const pixel_channel_max(
		mizuiro::color::channel_max<
			alpha_value
		>()
	);

	foreground.color(
		sprite::colored::color(
			sge::image::color::init::red =
			static_cast<
				sge::image::color::channel8
			>(
				(static_cast<health_type>(1) - remaining_health())
				* static_cast<health_type>(pixel_channel_max)
			),
			sge::image::color::init::green =
			static_cast<
				sge::image::color::channel8
			>(
				remaining_health() * static_cast<health_type>(pixel_channel_max)
			),
			sge::image::color::init::blue %= 0.0,
			sge::image::color::init::alpha %= 1.0
		)
	);
}
