#include "container.hpp"
#include "../sprite/normal/object.hpp"
#include "../sprite/normal/parameters.hpp"
#include "../sprite/index.hpp"
#include "../../../time_to_second.hpp"
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::entities::container::container(
	sprite::normal::system &_normal_system,
	size_type const _size,
	sprite::order const _order,
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
	)
{
	sprites_.reserve(
		_size
	);

	for(
		size_type index = 0;
		index < _size;
		++index
	)
		sprites_.push_back(
			object(
				sprite::normal::parameters()
				.system(
					&_normal_system
				)
				.order(
					_order
				)
				.size(
					_dim
				)
				.elements()
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
sanguis::client::draw2d::entities::container::update(
	sanguis::time_delta const &_time
)
{
	center_ +=
		draw2d::center(
			sanguis::time_to_second(
				_time
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
