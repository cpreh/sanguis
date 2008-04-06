#include "sprite.hpp"
#include <sge/math/vec_dim.hpp>
#include <boost/foreach.hpp>

sanguis::draw::sprite::sprite(
	const entity_id id,
	const sge::math::vector2& speed_,
	const sge::sprite::object& master_,
	const relative_pos::type relative)
: entity(id),
  speed_(speed_),
  pos_(
  	sge::math::structure_cast<sge::space_unit>(
		relative == relative_pos::topleft
		? master_.pos()
		: master_.pos() - master_.size() / 2)),
  relative(relative)
{
	add_sprite(
		master_);
		
	if(relative == relative_pos::center)
		master().set_center(master_.pos());
}

sanguis::draw::entity::sprite_vector sanguis::draw::sprite::to_sprites() const
{
	return sprites;
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

void sanguis::draw::sprite::add_sprite(const sge::sprite::object& s)
{
	sprites.push_back(s);
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
	return at(0).rotation();
}

const sge::math::vector2& sanguis::draw::sprite::speed() const
{
	return speed_;
}

void sanguis::draw::sprite::update_pos(const sge::sprite::point& p)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		switch(relative) {
		case relative_pos::topleft:
			s.pos() = p;
			break;
		case relative_pos::center:
			s.set_center(p);
			break;
		default:
			throw sge::exception(SGE_TEXT("Invalid relative_pos in sprite!"));
		}
}
