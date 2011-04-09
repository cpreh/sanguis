#include "container.hpp"
#include "../sprite/normal/object.hpp"
#include "../sprite/normal/parameters.hpp"
#include "../sprite/index.hpp"
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <boost/foreach.hpp>

sanguis::client::draw2d::entities::container::container(
	sprite::normal::system &_normal_system,
	size_type const _size,
	sprite::order const _order
)
:
	base(),
	with_orientation(),
	with_speed(),
	speed_(
		vector2::null()
	),
	pos_(
		vector2::null()
	)
{
	sprites_.reserve(
		_size
	);

	for(
		size_type i = 0;
		i < _size;
		++i
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
				.elements()
			)
		);
}

sanguis::client::draw2d::entities::container::~container()
{
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::container::center() const
{
	return
		sge::sprite::center(
			this->master()
		);
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::container::pos() const
{
	return
		this->master().pos();
}

void
sanguis::client::draw2d::entities::container::update(
	time_type const _time
)
{
	pos_ +=
		_time * this->speed();

	this->update_pos(
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			pos_
		)
	);
}

void
sanguis::client::draw2d::entities::container::pos(
	sprite::point const &_pos
)
{
	pos_ =
		fcppt::math::vector::structure_cast<
			vector2
		>(
			_pos
		);

	this->update_pos(
		_pos
	);
}

void
sanguis::client::draw2d::entities::container::dim(
	sprite::dim const &_dim
)
{
	BOOST_FOREACH(
		object &cur,
		sprites_
	)
		cur.size(
			_dim
		);
}

void
sanguis::client::draw2d::entities::container::orientation(
	sprite::rotation_type const _orientation
)
{
	BOOST_FOREACH(
		object &cur,
		sprites_
	)
		cur.rotation(
			_orientation
		);
}

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::container::orientation() const
{
	return
		this->master().rotation();
}

void
sanguis::client::draw2d::entities::container::speed(
	vector2 const &_speed
)
{
	speed_ = _speed;
}

sanguis::client::draw2d::vector2 const
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
sanguis::client::draw2d::entities::container::update_pos(
	sprite::point const &_pos
)
{
	BOOST_FOREACH(
		object &cur,
		sprites_
	)
		cur.pos(
			_pos
		);
}
