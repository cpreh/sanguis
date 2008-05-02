#include "player.hpp"
#include "z_ordering.hpp"
#include <sge/string.hpp>
#include <sge/math/abs.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/point_rotate.hpp>
#include <boost/none.hpp>
#include <iomanip>
#include <cassert>

namespace
{

//const sge::sprite::point rotation_point(0,0);

const sge::sprite::point player_body_center(25,32);
const sge::sprite::point player_leg_center(32,32);

sge::con::var<sge::space_unit> turning_speed(SGE_TEXT("player_turning_speed"),sge::su(0.4));
}

sanguis::draw::player::player(const entity_id id)
: model(id,
	SGE_TEXT("player")),
	angle_(sge::su(0)),
	target_angle(angle_)
{
	bottom_sprite().z() = z_ordering::player_lower;
	
	//top_sprite() = bottom_sprite();
	top_sprite().z() = z_ordering::player_upper;
	
	// FIXME: put the rotation point in a config file?
	top_sprite().rotate_around(
		player_body_center);
}


void sanguis::draw::player::speed(const sge::math::vector2 &v)
{
	sprite::speed(v);
	if (!v.is_null())
		target_angle = *sge::math::angle_to<sge::space_unit>(sge::math::vector2(),v);
}

void sanguis::draw::player::orientation(const sge::sprite::rotation_type u)
{
	model::orientation(u, 1); // TODO: better interface for this in model
	//model::orientation(u);
//	top_sprite().rotation(u);
}

void sanguis::draw::player::update(const time_type time)
{
	model::update(time);

	//sge::clog << "draw: player position: " << pos_ << "\n";

	// FIXME: load rotation point (see above)
	const sge::math::vector2 leg_center(sge::math::structure_cast<sge::space_unit>(player_leg_center));
	const sge::math::vector2 body_center(sge::math::structure_cast<sge::space_unit>(player_body_center));

	//sge::cout << "angle_ = " << angle_ << ", target_angle=" << target_angle << "\n";

	const sge::space_unit abs_angle = sge::math::rel_angle_to_abs(angle_),
	                      abs_target = sge::math::rel_angle_to_abs(target_angle);
	
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

	/* DEBUG
	if (!sge::math::nearly_equals(target_angle,angle_))
	{
		sge::cout << "a = " 
		          << sge::math::rad_to_deg(abs_angle) << ", t = " 
							<< sge::math::rad_to_deg(abs_target) << ", abs_dist = " 
							<< sge::math::rad_to_deg(abs_dist) << ", swap_dist = " 
							<< sge::math::rad_to_deg(swap_dist) << ", dir = " << dir << "\n";
	} */

	if (min_dist < time/turning_speed.value())
		angle_ = target_angle;
	else
		angle_ = sge::math::abs_angle_to_rel(abs_angle + dir * time/turning_speed.value());

	// player image is now rotated correctly
	//const sge::space_unit sprite_rotation = angle_ + sge::math::pi<sge::space_unit>()/sge::su(2);
	const sge::space_unit sprite_rotation = angle_;

	model::orientation(sprite_rotation, 0); // TODO: better interface for this in model
	//bottom_sprite().rotation(sprite_rotation);

	const sge::math::vector2 new_rotation = sge::math::point_rotate(
		leg_center,
		sge::math::vector2(sge::su(bottom_sprite().w()/2),sge::su(bottom_sprite().h()/2)),
		sprite_rotation);

	const sge::math::vector2 rot_abs = 
		sge::math::structure_cast<sge::space_unit>(bottom_sprite().pos())+new_rotation;

	const sge::math::vector2 top_pos = rot_abs - body_center;

	top_sprite().pos() = sge::math::structure_cast<sge::sprite::unit>(top_pos);
}

sge::sprite::object& sanguis::draw::player::bottom_sprite()
{
	return at(0);
}

sge::sprite::object& sanguis::draw::player::top_sprite()
{
	return at(1);
}

sge::space_unit sanguis::draw::player::health() const
{
	return model::health();
}

sge::space_unit sanguis::draw::player::max_health() const
{
	return model::max_health();
}

sge::sprite::point sanguis::draw::player::pos() const
{
	return sge::math::structure_cast<sge::sprite::unit>(model::pos());
}
