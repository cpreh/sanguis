#include "player.hpp"
#include "z_ordering.hpp"
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
	bottom_sprite().order(z_ordering::player_lower);
	
	//top_sprite() = bottom_sprite();
	top_sprite().order(z_ordering::player_upper);
	
	// FIXME: put the rotation point in a config file?
	top_sprite().rotate_around(
		player_body_center);
}


void sanguis::draw::player::speed(const sge::math::vector2 &v)
{
	sprite::speed(v);
	if (!v.is_null())
		model::orientation(*sge::math::angle_to<sge::space_unit>(sge::math::vector2(),v),0);
}

void sanguis::draw::player::orientation(const sge::sprite::rotation_type u)
{
	model::orientation(u, 1); // TODO: better interface for this in model
}

void sanguis::draw::player::update(const time_type time)
{
	model::update(time);

	sge::math::vector2 const leg_center(sge::math::structure_cast<sge::space_unit>(player_leg_center));
	sge::math::vector2 const body_center(sge::math::structure_cast<sge::space_unit>(player_body_center));

	sge::sprite::rotation_type const sprite_rotation = bottom_sprite().rotation();

	sge::math::vector2 const new_rotation = sge::math::point_rotate(
		leg_center,
		sge::math::vector2(sge::su(bottom_sprite().w()/2),sge::su(bottom_sprite().h()/2)),
		sprite_rotation);

	sge::math::vector2 const rot_abs = 
		sge::math::structure_cast<sge::space_unit>(bottom_sprite().pos())+new_rotation;

	sge::math::vector2 const top_pos = rot_abs - body_center;

	top_sprite().pos() = sge::math::structure_cast<sge::sprite::unit>(top_pos);
}

sanguis::draw::object& sanguis::draw::player::bottom_sprite()
{
	return at(0);
}

sanguis::draw::object& sanguis::draw::player::top_sprite()
{
	return at(1);
}
