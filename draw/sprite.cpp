#include "sprite.hpp"
#include <sge/math/vec_dim.hpp>
#include <boost/foreach.hpp>
#include <boost/none.hpp>

sanguis::draw::sprite::sprite(
	const entity_id id,
	const sprite_vector::size_type sz)
: entity(id)
{
	sprites.reserve(sz);
	for(sprite_vector::size_type i = 0; i < sz; ++i)
		sprites.push_back(
			sge::sprite::object(
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

sanguis::draw::entity::sprite_vector sanguis::draw::sprite::to_sprites() const
{
	return sprites;
}

void sanguis::draw::sprite::update(const time_type time)
{
	pos_ += time * speed();
	update_pos(sge::math::structure_cast<sge::sprite::unit>(pos_));
}

sge::sprite::object& sanguis::draw::sprite::at(const sprite_vector::size_type i)
{
	return sprites.at(i);
}

const sge::sprite::object& sanguis::draw::sprite::at(const sprite_vector::size_type i) const
{
	return sprites.at(i);
}

sge::sprite::object& sanguis::draw::sprite::master()
{
	return at(0);
}

const sge::sprite::object& sanguis::draw::sprite::master() const
{
	return at(0);
}

void sanguis::draw::sprite::orientation(const sge::space_unit o)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		s.rotation(o);
}

void sanguis::draw::sprite::speed(const sge::math::vector2& s)
{
	speed_ = s;
}

void sanguis::draw::sprite::pos(const sge::sprite::point& p)
{
	pos_ = sge::math::structure_cast<sge::space_unit>(p);
	update_pos(p);
}

void sanguis::draw::sprite::dim(const sge::sprite::dim& d)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		s.size() = d;
}

sge::space_unit sanguis::draw::sprite::orientation() const
{
	return master().rotation();
}

const sge::math::vector2& sanguis::draw::sprite::speed() const
{
	return speed_;
}

void sanguis::draw::sprite::update_pos(const sge::sprite::point& p)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		s.pos() = p;
}
