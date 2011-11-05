#include <sanguis/client/draw2d/entities/model/healthbar.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/sprite/colored/parameters.hpp>
#include <sanguis/client/draw2d/sprite/colored/color.hpp>
#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/exception.hpp>
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
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace
{

sanguis::client::draw2d::sprite::unit const
	border_size = 2,
	bar_height = 8;

}

sanguis::client::draw2d::entities::model::healthbar::healthbar(
	sprite::colored::system &_sys
)
:
	background_(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_lower
		)
		.system(
			_sys
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
	foreground_(
		sprite::colored::parameters()
		.order(
			z_ordering::healthbar_upper
		)
		.system(
			_sys
		)
		.elements()
	),
	health_(0),
	max_health_(0)
{
	this->recalc_health();
}

sanguis::client::draw2d::entities::model::healthbar::~healthbar()
{
}

void
sanguis::client::draw2d::entities::model::healthbar::update_health(
	client::health const _health,
	client::health const _max_health
)
{
	health_ = _health;

	max_health_ = _max_health;

	this->recalc_health();
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::healthbar::health() const
{
	return health_;
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::healthbar::max_health() const
{
	return max_health_;
}

void
sanguis::client::draw2d::entities::model::healthbar::attach_to(
	sprite::point const &_pos,
	sprite::dim const &_dim
)
{
	this->pos(
		sprite::point(
			_pos.x(),
			_pos.y() - bar_height
		)
	);

	this->dim(
		sprite::dim(
			std::max(
				_dim.w(),
				2 * border_size
			),
			bar_height
		)
	);
}

void
sanguis::client::draw2d::entities::model::healthbar::pos(
	sprite::point const &_pos
)
{
	background_.pos(
		_pos
	);

	foreground_.pos(
		this->inner_pos()
	);
}

void
sanguis::client::draw2d::entities::model::healthbar::dim(
	sprite::dim const &dim_
)
{
	background_.size(
		dim_
	);

	foreground_.size(
		inner_dim()
	);

	this->recalc_health();
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::model::healthbar::inner_pos() const
{
	return
		background_.pos()
		+ sprite::point(
			border_size,
			border_size
		);
}

sanguis::client::draw2d::sprite::dim const
sanguis::client::draw2d::entities::model::healthbar::inner_dim() const
{
	return
		background_.size()
		- sprite::dim(
			2 * border_size,
			2 * border_size
		);
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::healthbar::remaining_health() const
{
	return health_ / max_health_;
}

void
sanguis::client::draw2d::entities::model::healthbar::recalc_health()
{
	if(
		health_ > max_health_
	)
		return;

	if(
		fcppt::math::almost_zero(
			max_health_.get()
		)
	)
		// TODO!
		return;

	foreground_.w(
		static_cast<
			sprite::unit
		>(
			static_cast<
				client::health::value_type
			>(
				this->inner_dim().w()
			)
			* this->remaining_health().get()
		)
	);

	foreground_.color(
		sprite::colored::color(
			(sge::image::color::init::red() %=
				std::min(
					static_cast<
						client::health::value_type
					>(
						2.0f -
						2.0f
						*
						this->remaining_health().get()
					),
					static_cast<
						client::health::value_type
					>(
						1
					)
				)
			)
			(sge::image::color::init::green() %=
				std::min(
					static_cast<
						client::health::value_type
					>(
						1.4f
						*
						this->remaining_health().get()
					),
					static_cast<
						client::health::value_type
					>(
						0.7f
					)
				)
			)
			(sge::image::color::init::blue() %= 0.0)
			(sge::image::color::init::alpha() %= 1.0)
		)
	);
}
