#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_center.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_orientation.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_speed.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/size_or_texture_size.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/distance.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::container::container(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::client::draw2d::entities::order_vector const &_orders,
	sanguis::client::draw2d::sprite::dim const _dim,
	sanguis::client::draw2d::sprite::normal::color const _color
)
:
	sanguis::client::draw2d::entities::base(),
	sanguis::client::draw2d::entities::ifaces::with_center(),
	sanguis::client::draw2d::entities::ifaces::with_orientation(),
	sanguis::client::draw2d::entities::ifaces::with_speed(),
	speed_(
		sanguis::client::draw2d::speed::value_type::null()
	),
	center_(
		sanguis::client::draw2d::center::value_type::null()
	),
	sprites_(
		fcppt::algorithm::map<
			sanguis::client::draw2d::entities::container::sprite_vector
		>(
			_orders,
			[
				&_normal_system,
				_dim,
				_color
			](
				sanguis::client::draw2d::z_ordering const _order
			)
			{
				return
					sanguis::client::draw2d::sprite::normal::object(
						sge::sprite::roles::connection{} =
							_normal_system.connection(
								_order
							),
						sge::sprite::roles::size_or_texture_size{} =
							sanguis::client::draw2d::sprite::size_or_texture_size{
								_dim
							},
						sge::sprite::roles::color{} =
							_color,
						sge::sprite::roles::texture0{} =
							sanguis::client::draw2d::sprite::normal::object::texture_type{},
						sge::sprite::roles::rotation{} =
							sanguis::client::draw2d::sprite::normal::no_rotation(),
						sge::sprite::roles::center{} =
							sanguis::client::draw2d::sprite::point::null()
					);
			}
		)
	),
	move_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::seconds(
				1
			)
		)
	)
{
}

sanguis::client::draw2d::entities::container::~container()
{
}

sanguis::client::draw2d::sprite::center const
sanguis::client::draw2d::entities::container::center() const
{
	return
		sanguis::client::draw2d::sprite::center(
			this->master().center()
		);
}

sanguis::client::draw2d::radius const
sanguis::client::draw2d::entities::container::radius() const
{
	return
		sanguis::client::draw2d::radius(
			std::min(
				this->master().size().w(),
				this->master().size().h()
			)
			/
			2
		);
}

bool
sanguis::client::draw2d::entities::container::cursor_collision(
	sanguis::client::draw2d::sprite::center const _cursor
) const
{
	return
		fcppt::math::vector::distance<
			sanguis::client::draw2d::funit
		>(
			this->master().center(),
			_cursor.get()
		)
		<
		fcppt::cast::int_to_float<
			sanguis::client::draw2d::funit
		>(
			this->radius().get()
		);
}

void
sanguis::client::draw2d::entities::container::color(
	sanguis::client::draw2d::sprite::normal::color const &_color
)
{
	for(
		auto &sprite
		:
		sprites_
	)
		sprite.color(
			_color
		);
}

sanguis::client::draw2d::sprite::normal::color const
sanguis::client::draw2d::entities::container::color() const
{
	return
		this->master().color();
}

void
sanguis::client::draw2d::entities::container::center(
	sanguis::client::draw2d::sprite::center const &_center
)
{
	center_ =
		sanguis::client::draw2d::center(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::center::value_type,
				fcppt::cast::int_to_float_fun
			>(
				_center.get()
			)
		);

	this->update_center(
		_center
	);
}

sanguis::client::draw2d::center const
sanguis::client::draw2d::entities::container::float_center() const
{
	return
		center_;
}

void
sanguis::client::draw2d::entities::container::orientation(
	sanguis::client::draw2d::sprite::rotation const _orientation
)
{
	for(
		auto &sprite
		:
		sprites_
	)
		sprite.rotation(
			_orientation
		);
}

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::container::orientation() const
{
	return
		this->master().rotation();
}

void
sanguis::client::draw2d::entities::container::speed(
	sanguis::client::draw2d::speed const &_speed
)
{
	speed_ =
		_speed;
}

sanguis::client::draw2d::speed const
sanguis::client::draw2d::entities::container::speed() const
{
	return
		speed_;
}

sanguis::duration const
sanguis::client::draw2d::entities::container::movement_duration() const
{
	return
		sge::timer::elapsed<
			sanguis::duration
		>(
			move_timer_
		);
}

sanguis::client::draw2d::entities::container::object &
sanguis::client::draw2d::entities::container::at(
	sanguis::client::draw2d::sprite::index const &_index
)
{
	return
		sprites_.at(
			_index.get()
		);
}

sanguis::client::draw2d::entities::container::object const &
sanguis::client::draw2d::entities::container::at(
	sanguis::client::draw2d::sprite::index const &_index
) const
{
	return
		sprites_.at(
			_index.get()
		);
}

sanguis::client::draw2d::entities::container::object &
sanguis::client::draw2d::entities::container::master()
{
	return
		this->at(
			sanguis::client::draw2d::sprite::index(
				0
			)
		);
}

sanguis::client::draw2d::entities::container::object const &
sanguis::client::draw2d::entities::container::master() const
{
	return
		const_cast<
			container &
		>(
			*this
		).master();
}

sanguis::client::draw2d::entities::container::iterator
sanguis::client::draw2d::entities::container::begin()
{
	return
		sprites_.begin();
}

sanguis::client::draw2d::entities::container::iterator
sanguis::client::draw2d::entities::container::end()
{
	return
		sprites_.end();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::begin() const
{
	return
		sprites_.begin();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::end() const
{
	return
		sprites_.end();
}

void
sanguis::client::draw2d::entities::container::update()
{
	center_ +=
		sanguis::client::draw2d::center(
			sge::timer::elapsed_fractional_and_reset<
				sanguis::client::draw2d::funit
			>(
				move_timer_
			)
			*
			this->speed().get()
		);

	this->update_center(
		sanguis::client::draw2d::sprite::center(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::sprite::center::value_type,
				fcppt::cast::float_to_int_fun
			>(
				center_.get()
			)
		)
	);
}

void
sanguis::client::draw2d::entities::container::update_center(
	sanguis::client::draw2d::sprite::center const &_center
)
{
	for(
		auto &sprite
		:
		sprites_
	)
		sprite.center(
			_center.get()
		);
}
