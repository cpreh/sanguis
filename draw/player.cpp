#include "player.hpp"
#include "resource_factory.hpp"
#include <sge/string.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/point_rotate.hpp>
#include <cmath>

#if 0
namespace
{
sge::math::vector2 point_rotate(const sge::math::vector2 &point,const sge::math::vector2 &around,const sge::space_unit rot)
{
	const sge::space_unit sinx = std::sin(rot),
	                      cosx = std::cos(rot);

	const sge::math::basic_matrix<sge::space_unit,2,2> mat_rot(
		cosx, -sinx,
		sinx,  cosx); 
	
	return (mat_rot * (point - around)) + around;
}
}
#endif

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
		SGE_TEXT("player_walk")))
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

void sanguis::draw::player::orientation(sge::space_unit u)
{
	top_sprite().rotation(u);
}

void sanguis::draw::player::update(const time_type time)
{
	sprite::update(time);
	if(!speed().is_null())
		walk_animation.process();

	const sge::math::vector2 leg_center(sge::su(64),sge::su(80));
	const sge::math::vector2 body_center(sge::su(64),sge::su(80));

	const boost::optional<sge::space_unit> bottom_angle(
		sge::math::angle_to<sge::space_unit>(
			sge::math::vector2(0, 0),
			speed()));

	if(bottom_angle)
	{
		bottom_sprite().rotation(*bottom_angle);

		const sge::math::vector2 new_rotation = sge::math::point_rotate(
			leg_center,
			sge::math::vector2(sge::su(bottom_sprite().w()/2),sge::su(bottom_sprite().h()/2)),
			*bottom_angle);

		const sge::math::vector2 rot_abs = 
			sge::math::structure_cast<sge::space_unit>(bottom_sprite().pos())+new_rotation;

		const sge::math::vector2 top_pos = rot_abs - body_center;

		top_sprite().pos() = sge::math::structure_cast<sge::sprite_unit>(top_pos);
	//	top_sprite().set_center(
	//		top_sprite().pos()+sge::math::structure_cast<sge::sprite_unit>(new_rotation));
	}
}

sge::sprite& sanguis::draw::player::bottom_sprite()
{
	return at(0);
}

sge::sprite& sanguis::draw::player::top_sprite()
{
	return at(1);
}
