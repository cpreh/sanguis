#include "sprite.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>
#include <sge/console/console.hpp>
#include <boost/foreach.hpp>
#include <boost/none.hpp>
#include <algorithm>

namespace
{

const sge::sprite::rotation_type angle_speed 
	= sge::math::pi<sge::sprite::rotation_type>()
	  * static_cast<sge::sprite::rotation_type>(2);

sge::con::var<sge::space_unit> rotation_speed(SGE_TEXT("sprite_rot_speed"),sge::su(sge::math::pi<sge::space_unit>()/sge::su(2)));
}

sanguis::draw::sprite::sprite(
	const entity_id id,
	const sprite_vector::size_type sz)
: entity(id),desired_orientation(static_cast<sge::sprite::rotation_type>(0))
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

	//sge::cout << "orientation() = " << orientation() << ", desired=" << desired_orientation << "\n";

	const sge::space_unit abs_angle = sge::math::rel_angle_to_abs(orientation()),
	                      abs_target = sge::math::rel_angle_to_abs(desired_orientation);
	
	const sge::space_unit twopi = sge::su(2)*sge::math::pi<sge::space_unit>();

	assert(abs_angle >= sge::su(0) && abs_angle <= twopi);
	assert(abs_target >= sge::su(0) && abs_target <= twopi);

	const sge::space_unit abs_dist = sge::math::abs(abs_target - abs_angle);
	const sge::space_unit swap_dist = (abs_angle > abs_target) ? twopi-abs_angle+abs_target : twopi-abs_target+abs_angle;
	const sge::space_unit min_dist = std::min(swap_dist,abs_dist);

	assert(abs_dist >= sge::su(0) && swap_dist >= sge::su(0) && min_dist >= sge::su(0));

	sge::space_unit dir;
	if (abs_angle > abs_target)
		dir = (swap_dist > abs_dist) ? sge::su(-1) : sge::su(1);
	else
		dir = (swap_dist > abs_dist) ? sge::su(1) : sge::su(-1);

	const sge::space_unit turning_speed = rotation_speed.value();

	sge::space_unit new_angle;

	if (min_dist < time/turning_speed)
		new_angle = desired_orientation;
	else
		new_angle = sge::math::abs_angle_to_rel(abs_angle + dir * time/turning_speed);

	update_orientation(new_angle);
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
	desired_orientation = o;
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

void sanguis::draw::sprite::visible(const bool v)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
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
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		s.pos() = p;
}

void sanguis::draw::sprite::update_orientation(sge::sprite::rotation_type o)
{
	BOOST_FOREACH(sge::sprite::object& s, sprites)
		s.rotation(o);
}
