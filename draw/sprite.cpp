#include "sprite.hpp"
#include <boost/foreach.hpp>
#include <boost/none.hpp>
#include <algorithm>

sanguis::draw::sprite::sprite(
	entity_id const id,
	system &sys,
	sprite_vector::size_type const sz)
: entity(
	id,
	sys)
{
	sprites.reserve(sz);
	for(sprite_vector::size_type i = 0; i < sz; ++i)
		sprites.push_back(
			object(
				get_system(),
				1, // FIXME
				boost::none,
				boost::none,
				boost::none,
				boost::none));
}

const sge::sprite::point
sanguis::draw::sprite::center() const
{
	return master().center();
}

void sanguis::draw::sprite::update(const time_type time)
{
	pos_ += time * speed();
	update_pos(sge::math::structure_cast<sge::sprite::unit>(pos_));
}

sanguis::draw::object &
sanguis::draw::sprite::at(const sprite_vector::size_type i)
{
	return sprites.at(i);
}

sanguis::draw::object const &
sanguis::draw::sprite::at(const sprite_vector::size_type i) const
{
	return sprites.at(i);
}

sanguis::draw::object &
sanguis::draw::sprite::master()
{
	return at(0);
}

sanguis::draw::object const &
sanguis::draw::sprite::master() const
{
	return at(0);
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

void sanguis::draw::sprite::orientation(const sge::space_unit o)
{
	BOOST_FOREACH(object &s, sprites)
		s.rotation(o);
}

void sanguis::draw::sprite::speed(const sge::math::vector2& s)
{
	speed_ = s;
}

sge::math::vector2 sanguis::draw::sprite::pos() const
{
	return pos_;
}

void sanguis::draw::sprite::pos(const sge::sprite::point& p)
{
	pos_ = sge::math::structure_cast<sge::space_unit>(p);
	update_pos(p);
}

void sanguis::draw::sprite::dim(const sge::sprite::dim& d)
{
	BOOST_FOREACH(object &s, sprites)
		s.size() = d;
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

const sge::math::vector2& sanguis::draw::sprite::speed() const
{
	return speed_;
}

void sanguis::draw::sprite::update_pos(const sge::sprite::point& p)
{
	BOOST_FOREACH(object &s, sprites)
		s.pos() = p;
}
