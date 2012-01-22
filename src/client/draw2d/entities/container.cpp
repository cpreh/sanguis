#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/parameters.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::entities::container::container(
	sanguis::diff_clock const &_diff_clock,
	sprite::normal::system &_normal_system,
	entities::order_vector const &_orders,
	sprite::dim const &_dim
)
:
	base(),
	with_orientation(),
	with_speed(),
	speed_(
		draw2d::speed::value_type::null()
	),
	center_(
		draw2d::center::value_type::null()
	),
	sprites_(),
	move_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			fcppt::chrono::seconds(
				1
			)
		)
	)
{
	sprites_.reserve(
		_orders.size()
	);

	for(
		entities::order_vector::const_iterator it(
			_orders.begin()
		);
		it != _orders.end();
		++it
	)
		sprites_.push_back(
			object(
				sprite::normal::parameters()
				.connection(
					_normal_system.connection(
						*it
					)
				)
				.size(
					_dim
				)
			)
		);
}

sanguis::client::draw2d::entities::container::~container()
{
}

sanguis::client::draw2d::sprite::center const
sanguis::client::draw2d::entities::container::center() const
{
	return
		draw2d::sprite::center(
			sge::sprite::center(
				this->master()
			)
		);
}

void
sanguis::client::draw2d::entities::container::update()
{
	center_ +=
		draw2d::center(
			sge::timer::elapsed_fractional_and_reset<
				draw2d::funit
			>(
				move_timer_
			)
			*
			this->speed().get()
		);

	this->update_center(
		sprite::center(
			fcppt::math::vector::structure_cast<
				sprite::center::value_type
			>(
				center_.get()
			)
		)
	);
}

void
sanguis::client::draw2d::entities::container::center(
	sprite::center const &_center
)
{
	center_ =
		draw2d::center(
			fcppt::math::vector::structure_cast<
				draw2d::center::value_type
			>(
				_center.get()
			)
		);

	this->update_center(
		_center
	);
}

void
sanguis::client::draw2d::entities::container::orientation(
	sprite::rotation const _orientation
)
{
	for(
		sprite_vector::iterator it(
			sprites_.begin()
		);
		it != sprites_.end();
		++it
	)
		it->rotation(
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
	draw2d::speed const &_speed
)
{
	speed_ = _speed;
}

sanguis::client::draw2d::speed const
sanguis::client::draw2d::entities::container::speed() const
{
	return speed_;
}

sanguis::client::draw2d::entities::container::object &
sanguis::client::draw2d::entities::container::at(
	sprite::index const &_index
)
{
	return
		sprites_.at(
			_index.get()
		);
}

sanguis::client::draw2d::entities::container::object const &
sanguis::client::draw2d::entities::container::at(
	sprite::index const &_index
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
			sprite::index(0)
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
	return sprites_.begin();
}

sanguis::client::draw2d::entities::container::iterator
sanguis::client::draw2d::entities::container::end()
{
	return sprites_.end();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::begin() const
{
	return sprites_.begin();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::end() const
{
	return sprites_.end();
}

void
sanguis::client::draw2d::entities::container::update_center(
	sprite::center const &_center
)
{
	for(
		sprite_vector::iterator it(
			sprites_.begin()
		);
		it != sprites_.end();
		++it
	)
		sge::sprite::center(
			*it,
			_center.get()
		);
}
