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
	sprite::normal::system &normal_system_,
	size_type const sz,
	sprite::order const order
)
:
	base(),
	with_orientation(),
	with_speed(),
	speed_(vector2::null()),
	pos_(vector2::null())
{
	sprites.reserve(sz);

	for(size_type i = 0; i < sz; ++i)
		sprites.push_back(
			object(
				sprite::normal::parameters()
				.system(
					&normal_system_
				)
				.order(
					order
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
	return sge::sprite::center(
		master()
	);
}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::container::pos() const
{
	return master().pos();
}

void
sanguis::client::draw2d::entities::container::update(
	time_type const time
)
{
	pos_ += time * speed();

	update_pos(
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			pos_
		)
	);
}

void
sanguis::client::draw2d::entities::container::pos(
	sprite::point const &p
)
{
	pos_ = fcppt::math::vector::structure_cast<
		vector2
	>(
		p
	);

	update_pos(p);
}

void
sanguis::client::draw2d::entities::container::dim(
	sprite::dim const &d
)
{
	BOOST_FOREACH(object &s, sprites)
		s.size(d);
}

void
sanguis::client::draw2d::entities::container::orientation(
	sprite::rotation_type const o
)
{
	BOOST_FOREACH(object &s, sprites)
		s.rotation(o);
}

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::container::orientation() const
{
	return master().rotation();
}

void
sanguis::client::draw2d::entities::container::speed(
	vector2 const &s
)
{
	speed_ = s;
}

sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::entities::container::speed() const
{
	return speed_;
}

sanguis::client::draw2d::entities::container::object &
sanguis::client::draw2d::entities::container::at(
	sprite::index const &i
)
{
	return sprites.at(i.get());
}

sanguis::client::draw2d::entities::container::object const &
sanguis::client::draw2d::entities::container::at(
	sprite::index const &i
) const
{
	return sprites.at(i.get());
}

sanguis::client::draw2d::entities::container::object &
sanguis::client::draw2d::entities::container::master()
{
	return at(
		sprite::index(0)
	);
}

sanguis::client::draw2d::entities::container::object const &
sanguis::client::draw2d::entities::container::master() const
{
	return const_cast<container &>(*this).master();
}

sanguis::client::draw2d::entities::container::iterator
sanguis::client::draw2d::entities::container::begin()
{
	return sprites.begin();
}

sanguis::client::draw2d::entities::container::iterator
sanguis::client::draw2d::entities::container::end()
{
	return sprites.end();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::begin() const
{
	return sprites.begin();
}

sanguis::client::draw2d::entities::container::const_iterator
sanguis::client::draw2d::entities::container::end() const
{
	return sprites.end();
}

void
sanguis::client::draw2d::entities::container::update_pos(
	sprite::point const &p
)
{
	BOOST_FOREACH(object &s, sprites)
		s.pos(p);
}
