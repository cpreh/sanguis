#include "sprite.hpp"
#include "sprite_part_index.hpp"
#include "object.hpp"
#include <sge/sprite/intrusive/parameters.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/none.hpp>

sanguis::draw::sprite::sprite(
	draw::environment const &env,
	entity_id const id,
	size_type const sz,
	sge::sprite::intrusive::order const order)
:
	entity(
		env,
		id),
	speed_(vector2::null()),
	pos_(vector2::null())
{
	sprites.reserve(sz);
	for(size_type i = 0; i < sz; ++i)
		sprites.push_back(
			object(
				sge::sprite::intrusive::parameters(
					system(),
					order
				)
			)
		);
}

sge::sprite::point const
sanguis::draw::sprite::center() const
{
	return master().center();
}

sge::sprite::point const
sanguis::draw::sprite::pos() const
{
	return master().pos();
}

void sanguis::draw::sprite::update(
	time_type const time)
{
	pos_ += time * speed();
	update_pos(
		sge::math::vector::structure_cast<
			sge::sprite::point
		>(
			pos_));
}

sanguis::draw::object &
sanguis::draw::sprite::at(
	sprite_part_index const &i)
{
	return sprites.at(i.get());
}

sanguis::draw::object const &
sanguis::draw::sprite::at(
	sprite_part_index const &i) const
{
	return sprites.at(i.get());
}

sanguis::draw::object &
sanguis::draw::sprite::master()
{
	return at(sprite_part_index(0));
}

sanguis::draw::object const &
sanguis::draw::sprite::master() const
{
	return const_cast<sprite &>(*this).master();
}

sanguis::draw::sprite::iterator
sanguis::draw::sprite::begin()
{
	return sprites.begin();
}

sanguis::draw::sprite::iterator
sanguis::draw::sprite::end()
{
	return sprites.end();
}

sanguis::draw::sprite::const_iterator
sanguis::draw::sprite::begin() const
{
	return sprites.begin();
}

sanguis::draw::sprite::const_iterator
sanguis::draw::sprite::end() const
{
	return sprites.end();
}

void sanguis::draw::sprite::orientation(const funit o)
{
	BOOST_FOREACH(object &s, sprites)
		s.rotation(o);
}

void sanguis::draw::sprite::speed(
	vector2 const &s)
{
	speed_ = s;
}

void sanguis::draw::sprite::pos(
	sge::sprite::point const &p)
{
	pos_ = sge::math::vector::structure_cast<
		vector2
	>(
		p);
	update_pos(p);
}

void sanguis::draw::sprite::dim(const sge::sprite::dim& d)
{
	BOOST_FOREACH(object &s, sprites)
		s.size() = d;
}

void sanguis::draw::sprite::color(sge::sprite::color const c)
{
	BOOST_FOREACH(object &s, sprites)
		s.color(c);
}

void sanguis::draw::sprite::visible(const bool v)
{
	BOOST_FOREACH(object &s, sprites)
		s.visible(v);
}

sge::sprite::rotation_type
sanguis::draw::sprite::orientation() const
{
	return master().rotation();
}

sanguis::draw::vector2 const
sanguis::draw::sprite::speed() const
{
	return speed_;
}

void sanguis::draw::sprite::update_pos(
	sge::sprite::point const &p)
{
	BOOST_FOREACH(object &s, sprites)
		s.pos() = p;
}

void sanguis::draw::sprite::transfer(
	draw::system &sys)
{
	BOOST_FOREACH(object &s, sprites)
		s.transfer(sys);
}
