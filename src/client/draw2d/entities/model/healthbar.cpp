#include <sanguis/exception.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/health_value.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/colored/color.hpp>
#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sanguis/client/draw2d/sprite/colored/parameters.hpp>
#include <sanguis/client/draw2d/sprite/colored/object.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_decl.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <fcppt/format.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
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
	sanguis::client::draw2d::sprite::colored::system &_sys
)
:
	background_(
		sanguis::client::draw2d::sprite::colored::parameters()
		.connection(
			_sys.connection(
				sanguis::client::draw2d::z_ordering::healthbar_lower
			)
		)
		.color(
			sge::image::color::any::convert<
				sanguis::client::draw2d::sprite::colored::color_format
			>(
				sge::image::color::predef::black()
			)
		)
	),
	foreground_(
		sanguis::client::draw2d::sprite::colored::parameters()
		.connection(
			_sys.connection(
				sanguis::client::draw2d::z_ordering::healthbar_upper
			)
		)
	),
	health_(
		0.f
	),
	max_health_(
		0.f
	)
{
	this->recalc_health();
}

sanguis::client::draw2d::entities::model::healthbar::~healthbar()
{
}

void
sanguis::client::draw2d::entities::model::healthbar::update_health(
	sanguis::client::health const _health,
	sanguis::client::max_health const _max_health
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

sanguis::client::max_health const
sanguis::client::draw2d::entities::model::healthbar::max_health() const
{
	return max_health_;
}

void
sanguis::client::draw2d::entities::model::healthbar::attach_to(
	sanguis::client::draw2d::sprite::point const &_pos,
	sanguis::client::draw2d::sprite::dim const &_dim
)
{
	this->pos(
		sanguis::client::draw2d::sprite::point(
			_pos.x(),
			_pos.y() - bar_height
		)
	);

	this->dim(
		sanguis::client::draw2d::sprite::dim(
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
	sanguis::client::draw2d::sprite::point const &_pos
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
	sanguis::client::draw2d::sprite::dim const &dim_
)
{
	background_.size(
		dim_
	);

	foreground_.size(
		this->inner_dim()
	);

	this->recalc_health();
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::model::healthbar::inner_pos() const
{
	return
		background_.pos()
		+
		sanguis::client::draw2d::sprite::point(
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
	return
		sanguis::client::health(
			health_.get()
			/
			max_health_.get()
		);
}

void
sanguis::client::draw2d::entities::model::healthbar::recalc_health()
{
	if(
		health_.get() > max_health_.get()
	)
		return;

	if(
		max_health_.get()
		<
		static_cast<
			sanguis::client::health_value
		>(
			0.01f
		)
	)
	{
		foreground_.size(
			sanguis::client::draw2d::sprite::dim::null()
		);

		background_.size(
			sanguis::client::draw2d::sprite::dim::null()
		);

		return;
	}

	foreground_.w(
		static_cast<
			sanguis::client::draw2d::sprite::unit
		>(
			static_cast<
				sanguis::client::health::value_type
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
						sanguis::client::health::value_type
					>(
						2.0f -
						2.0f
						*
						this->remaining_health().get()
					),
					static_cast<
						sanguis::client::health::value_type
					>(
						1
					)
				)
			)
			(sge::image::color::init::green() %=
				std::min(
					static_cast<
						sanguis::client::health::value_type
					>(
						1.4f
						*
						this->remaining_health().get()
					),
					static_cast<
						sanguis::client::health::value_type
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
