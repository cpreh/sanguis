#include "player.hpp"
#include "resource_factory.hpp"
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
template<typename T>
bool is_between(const T &t,const T &l,const T &r)
{
	return t >= l && t <= r;
}

sge::space_unit rel_angle_to_abs(const sge::space_unit a)
{
	assert(is_between(a,-sge::math::pi<sge::space_unit>(),sge::math::pi<sge::space_unit>()));

	if (sge::math::almost_zero(a))
		return sge::su(0);

	return a > sge::su(0) ? a : sge::su(2)*sge::math::pi<sge::space_unit>()+a;
}

sge::space_unit abs_angle_to_rel(sge::space_unit a)
{
	a = sge::math::mod(a,sge::su(2)*sge::math::pi<sge::space_unit>());

	if (is_between(a,-sge::math::pi<sge::space_unit>(),sge::math::pi<sge::space_unit>()))
		return a;

	return a > sge::math::pi<sge::space_unit>() 
		? a-sge::su(2)*sge::math::pi<sge::space_unit>() 
		: a;
}

const sge::sprite::point rotation_point(0,0);

}

sanguis::draw::player::player(
	const entity_id id,
	const sge::sprite::point& pos,
	const sge::space_unit angle,
	const sge::math::vector2& speed)
: sprite(
	id,
	speed,
	sge::sprite::object(
		pos,
		resource::texture(SGE_TEXT("player_upper_pistol")),
		sge::sprite::texture_dim,
		boost::none,
		z_ordering::player_lower,
		angle),
	relative_pos::center),
  walk_animation(
  	resource::animation(
		SGE_TEXT("player/lower"))),
	angle_(sge::su(0)),
	target_angle(angle_),
	turning_speed(SGE_TEXT("player_turning_speed"),sge::su(0.5))
{
	sge::sprite::object skel_sprite(master());
	skel_sprite.z() = z_ordering::player_upper;
	add_sprite(skel_sprite);

	walk_animation.bind(&bottom_sprite());

	// FIXME: put the rotation point in a config file?
	top_sprite().rotate_around(
		rotation_point);
}


void sanguis::draw::player::speed(const sge::math::vector2 &v)
{
	sprite::speed(v);
	if (!v.is_null())
		target_angle = *sge::math::angle_to<sge::space_unit>(sge::math::vector2(),v);
}

void sanguis::draw::player::orientation(sge::space_unit u)
{
	//top_sprite().rotation(u + sge::math::pi<sge::space_unit>() / sge::su(2));
	// player image is now rotated correctly
	top_sprite().rotation(u);
}


void sanguis::draw::player::update(const time_type time)
{
	sprite::update(time);
	if(!sprite::speed().is_null())
		walk_animation.process();

	// FIXME: load rotation point (see above)
	const sge::math::vector2 leg_center(sge::math::structure_cast<sge::space_unit>(rotation_point));
	const sge::math::vector2 body_center(leg_center);

	const sge::space_unit abs_angle = rel_angle_to_abs(angle_),
	                      abs_target = rel_angle_to_abs(target_angle);
	
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
		angle_ = abs_angle_to_rel(abs_angle + dir * time/turning_speed.value());

	// player image is now rotated correctly
	//const sge::space_unit sprite_rotation = angle_ + sge::math::pi<sge::space_unit>()/sge::su(2);
	const sge::space_unit sprite_rotation = angle_;

	bottom_sprite().rotation(sprite_rotation);

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
