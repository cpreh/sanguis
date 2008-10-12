#include "player.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "../client/next_id.hpp"
#include <sge/string.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/constants.hpp>
#include <sge/console/var_impl.hpp>
#include <sge/math/point_rotate.hpp>
#include <boost/none.hpp>
#include <algorithm>
#include <cmath>
#include <cassert>

namespace
{

const sge::sprite::point player_body_center(25,32);
const sge::sprite::point player_leg_center(32,32);

sge::con::var<sge::space_unit> turning_speed(SGE_TEXT("player_turning_speed"),sge::su(0.4));

sanguis::draw::sprite_part_index const
	top(0),
	bottom(1);

}

sanguis::draw::player::player(
	entity_id const id,
	system &sys)
: model(
	id,
	sys,
	SGE_TEXT("player"),
	z_ordering::model_generic),
  angle_(sge::su(0)),
  target_angle(angle_),
  reaper_(
  	client::next_id(),
	sys,
	*this)
{
	at(bottom).order(z_ordering::player_lower);
	
	at(top).order(z_ordering::player_upper);
	
	// FIXME: put the rotation point in a config file?
	at(top).rotate_around(
		player_body_center);
}


void sanguis::draw::player::speed(const sge::math::vector2 &v)
{
	model::speed(v);
	if (!v.is_null())
		model::orientation(
			*sge::math::angle_to<sge::space_unit>(
				sge::math::vector2(),
				v),
			0);
}

void sanguis::draw::player::orientation(const sge::sprite::rotation_type u)
{
	model::orientation(u, 1); // TODO: better interface for this in model
}

void sanguis::draw::player::update(
	time_type const time)
{
	model::update(time);

	sge::math::vector2 const
		leg_center(
			sge::math::structure_cast<sge::space_unit>(
				player_leg_center)),
		body_center(
			sge::math::structure_cast<sge::space_unit>(
				player_body_center));

	sge::sprite::rotation_type const sprite_rotation = at(bottom).rotation();

	sge::math::vector2 const new_rotation = sge::math::point_rotate(
		leg_center,
		sge::math::vector2(sge::su(at(bottom).w()/2),sge::su(at(bottom).h()/2)),
		sprite_rotation);

	sge::math::vector2 const rot_abs = 
		sge::math::structure_cast<sge::space_unit>(at(bottom).pos())+new_rotation;

	sge::math::vector2 const top_pos = rot_abs - body_center;

	at(top).pos() = sge::math::structure_cast<sge::sprite::unit>(top_pos);

	reaper_.update(time);
}

void sanguis::draw::player::change_animation(
	animation_type::type const anim)
{
	part(bottom).animation(
		walking()
		? animation_type::walking
		: animation_type::none);
	
	part(top).animation(
		anim);
}
