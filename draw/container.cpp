#include "sprite.hpp"
#include "sprite_part_index.hpp"
#include "sprite/normal/object.hpp"
#include "sprite/normal/parameters.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/none.hpp>

sanguis::draw::container::sprite(
	draw::environment const &env,
	entity_id const id,
	size_type const sz,
	sprite::order const order
)
:
	entity(
		env,
		id
	),
	speed_(vector2::null()),
	pos_(vector2::null())
{
	sprites.reserve(sz);

	for(size_type i = 0; i < sz; ++i)
		sprites.push_back(
			sprite::normal::object(
				sprite::normal::parameters()
				.system(
					&env.normal_system()
				)
				.order(
					order
				)
				.visible(
					true
				)
				.elements()
			)
		);
}

sanguis::draw::sprite::point const
sanguis::draw::container::center() const
{
	return master().center();
}

sanguis::draw::sprite::point const
sanguis::draw::container::pos() const
{
	return master().pos();
}

void
sanguis::draw::container::update(
	time_type const time
)
{
	pos_ += time * speed();

	update_pos(
		sge::math::vector::structure_cast<
			sprite::point
		>(
			pos_
		)
	);
}

sanguis::draw::object &
sanguis::draw::container::at(
	sprite_part_index const &i
)
{
	return sprites.at(i.get());
}

sanguis::draw::object const &
sanguis::draw::container::at(
	sprite_part_index const &i
) const
{
	return sprites.at(i.get());
}

sanguis::draw::object &
sanguis::draw::container::master()
{
	return at(sprite_part_index(0));
}

sanguis::draw::object const &
sanguis::draw::container::master() const
{
	return const_cast<sprite &>(*this).master();
}

sanguis::draw::container::iterator
sanguis::draw::container::begin()
{
	return sprites.begin();
}

sanguis::draw::container::iterator
sanguis::draw::container::end()
{
	return sprites.end();
}

sanguis::draw::container::const_iterator
sanguis::draw::container::begin() const
{
	return sprites.begin();
}

sanguis::draw::container::const_iterator
sanguis::draw::container::end() const
{
	return sprites.end();
}

void sanguis::draw::container::orientation(const funit o)
{
	BOOST_FOREACH(object &s, sprites)
		s.rotation(o);
}

void sanguis::draw::container::speed(
	vector2 const &s)
{
	speed_ = s;
}

void sanguis::draw::container::pos(
	sprite::point const &p
)
{
	pos_ = sge::math::vector::structure_cast<
		vector2
	>(
		p);
	update_pos(p);
}

void sanguis::draw::container::dim(
	sprite::dim const &d
)
{
	BOOST_FOREACH(object &s, sprites)
		s.size() = d;
}

void sanguis::draw::container::visible(const bool v)
{
	BOOST_FOREACH(object &s, sprites)
		s.visible(v);
}

sanguis::draw::sprite::rotation_type
sanguis::draw::container::orientation() const
{
	return master().rotation();
}

sanguis::draw::vector2 const
sanguis::draw::container::speed() const
{
	return speed_;
}

void
sanguis::draw::container::update_pos(
	sprite::point const &p
)
{
	BOOST_FOREACH(object &s, sprites)
		s.pos() = p;
}
