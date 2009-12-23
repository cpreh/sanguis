#include "player.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "sprite/point.hpp"
#include "../client/next_id.hpp"
#include <fcppt/text.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/vector/angle_between.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/console/var_impl.hpp>
#include <sge/math/point_rotate.hpp>
#include <boost/none.hpp>
#include <algorithm>
#include <cmath>

namespace
{

sanguis::draw::sprite::point const
	player_body_center(25,32),
	player_leg_center(32,32);

sanguis::draw::sprite_part_index const
	top(1),
	bottom(0);

}

sanguis::draw::player::player(
	draw::environment const &env,
	entity_id const id)
:
	model(
		env,
		id,
		FCPPT_TEXT("player"),
		z_ordering::model_generic,
		true,
		draw::remove_action::render_dead),
	angle_(static_cast<funit>(0)),
	target_angle(angle_)
{
	at(bottom).order(z_ordering::player_lower);
	
	at(top).order(z_ordering::player_upper);
	
	// FIXME: put the rotation point in a config file?
/*	at(top).rotate_around(
		player_body_center);*/
}


void sanguis::draw::player::speed(
	vector2 const &v)
{
	model::speed(v);
	if (!is_null(v))
		model::orientation(
			*sge::math::vector::angle_between<funit>(
				vector2::null(),
				v),
			0);
}

void sanguis::draw::player::orientation(
	sprite::rotation_type const u)
{
	model::orientation(u, 1); // TODO: better interface for this in model
}

void sanguis::draw::player::update(
	time_type const time)
{
	model::update(time);

	vector2 const
		leg_center(
			sge::math::vector::structure_cast<
				vector2
			>(
				player_leg_center)),
		body_center(
			sge::math::vector::structure_cast<
				vector2
			>(
				player_body_center));

	sprite::rotation_type const sprite_rotation = at(bottom).rotation();

	vector2 const new_rotation = sge::math::point_rotate(
		leg_center,
		vector2(
			static_cast<funit>(at(bottom).w()/2),
			static_cast<funit>(at(bottom).h()/2)),
		sprite_rotation);

	vector2 const
		rot_abs = sge::math::vector::structure_cast<
			vector2
		>(
			at(bottom).pos())+new_rotation,
		top_pos = rot_abs - body_center;

	at(top).pos(
		sge::math::vector::structure_cast<
			sprite::point
		>(
			top_pos
		)
	);
}
