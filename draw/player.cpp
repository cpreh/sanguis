#include "player.hpp"
#include "resource_factory.hpp"
#include <sge/string.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/point_rotate.hpp>

namespace
{
template<typename T>
T signum(const T &t)
{
	if (t > static_cast<T>(0)) 
		return static_cast<T>(1);
	if (t < static_cast<T>(0))
		return static_cast<T>(-1);
	return static_cast<T>(0);
}
}

sanguis::draw::player::player(
	const entity_id id,
	const sge::sprite::point& pos_,
	const sge::space_unit angle,
	const sge::math::vector2& speed)
: sprite(
	id,
	speed),
  walk_animation(
  	resource::animation(
		SGE_TEXT("player_walk"))),
	angle_(sge::su(0)),target_angle(sge::su(0)),
	turning_speed(SGE_TEXT("player_turning_speed"),sge::su(2))
{
	pos(pos_);
	sge::sprite skel_sprite(
		sge::sprite(
			pos_,
			resource::texture(SGE_TEXT("player_up")),
			sge::sprite_texture_dim,
			sge::colors::white,
			-1,
			angle));
	add_sprite(skel_sprite);

	skel_sprite.z() = static_cast<sge::space_unit>(-2);
	add_sprite(skel_sprite);

	walk_animation.bind(&bottom_sprite());

	top_sprite().rotate_around(
		sge::sprite::point(
			64,80));
}


void sanguis::draw::player::speed(const sge::math::vector2 &v)
{
	sprite::speed(v);
	if (!v.is_null())
	{
		target_angle = *sge::math::angle_to<sge::space_unit>(sge::math::vector2(),v);
	//	sge::cout << "v: " << v << ", angle: " << target_angle-sge::su(0.5)*sge::math::pi<sge::space_unit>() << "\n";
	}
}


void sanguis::draw::player::orientation(sge::space_unit u)
{
	top_sprite().rotation(u);
}

void sanguis::draw::player::update(const time_type time)
{
	sprite::update(time);
	if(!sprite::speed().is_null())
		walk_animation.process();

	const sge::math::vector2 leg_center(sge::su(64),sge::su(80));
	const sge::math::vector2 body_center(sge::su(64),sge::su(80));

	if (!sge::math::nearly_equals(angle_,target_angle))
	//	sge::cout << "angle: " << angle_ << ", target_angle: " << target_angle-sge::su(0.5)*sge::math::pi<sge::space_unit>() << "\n";
		angle_ += signum(target_angle - angle_) * (turning_speed.value() * time);
	
	//const sge::math::vector2 local_speed = angle_to_vector(angle_);
	//const sge::math::vector2 local_speed = (speed.is_null()) ? last_speed : speed();

	/*
	const boost::optional<sge::space_unit> bottom_angle(
		sge::math::angle_to<sge::space_unit>(
			sge::math::vector2(0, 0),
			local_speed));
	*/

	bottom_sprite().rotation(angle_);

	const sge::math::vector2 new_rotation = sge::math::point_rotate(
		leg_center,
		sge::math::vector2(sge::su(bottom_sprite().w()/2),sge::su(bottom_sprite().h()/2)),
		angle_);

	const sge::math::vector2 rot_abs = 
		sge::math::structure_cast<sge::space_unit>(bottom_sprite().pos())+new_rotation;

	const sge::math::vector2 top_pos = rot_abs - body_center;

	top_sprite().pos() = sge::math::structure_cast<sge::sprite_unit>(top_pos);
}

sge::sprite& sanguis::draw::player::bottom_sprite()
{
	return at(0);
}

sge::sprite& sanguis::draw::player::top_sprite()
{
	return at(1);
}
