#include <boost/foreach.hpp>
#include "sprite.hpp"

sanguis::draw::sprite::sprite(
	const entity_id id,
	const sge::math::vector2& speed_)
: entity(id),
  speed_(speed_),
  pos_(0,0)
{}

sanguis::draw::sprite::sprite(
	const entity_id id,
	const sge::sprite::point& spos,
	const sge::sprite::dim& sdim,
	const sge::virtual_texture_ptr tex,
	const sge::sprite::rotation_type angle,
	const sge::math::vector2& speed_,
	const sge::space_unit z)
: entity(id),
  speed_(speed_),
  pos_(0,0)
{
	//sge::cout << "adding sprite with id " << id << " and position " << spos << "\n";
	add_sprite(
		sge::sprite(
			spos,
			tex,
			sdim,
			sge::colors::white,
			z,
			angle));
}

sanguis::draw::entity::sprite_vector sanguis::draw::sprite::to_sprites() const
{
	return sprites;
}

const sge::sprite::point
sanguis::draw::sprite::center() const
{
	return at(0).center();
}

void sanguis::draw::sprite::update(const time_type time)
{
	pos_ += time * speed();
	update_pos(sge::math::structure_cast<sge::sprite_unit>(pos_));
}

sge::sprite& sanguis::draw::sprite::at(const sprite_vector::size_type i)
{
	return sprites.at(i);
}

const sge::sprite& sanguis::draw::sprite::at(const sprite_vector::size_type i) const
{
	return sprites.at(i);
}

void sanguis::draw::sprite::add_sprite(const sge::sprite& s)
{
	sprites.push_back(s);
}

void sanguis::draw::sprite::orientation(const sge::space_unit o)
{
	BOOST_FOREACH(sge::sprite& s, sprites)
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
	BOOST_FOREACH(sge::sprite& s, sprites)
		s.size() = d;
}

sge::space_unit sanguis::draw::sprite::orientation() const
{
	return at(0).rotation();
}

const sge::math::vector2& sanguis::draw::sprite::speed() const
{
	return speed_;
}

void sanguis::draw::sprite::update_pos(const sge::sprite::point& p)
{
	BOOST_FOREACH(sge::sprite& s, sprites)
		s.pos() = p;
}
