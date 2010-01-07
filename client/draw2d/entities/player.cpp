#include "player.hpp"
#include "../z_ordering.hpp"
#include "../sprite/index.hpp"
#include "../sprite/point.hpp"
#include <sge/sprite/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/angle_between.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/point_rotate.hpp>

namespace
{

sanguis::client::draw2d::sprite::point const
	player_body_center(25,32),
	player_leg_center(32,32);

sanguis::client::draw2d::sprite::index const
	top(1),
	bottom(0);

}

sanguis::client::draw2d::entities::player::player(
	model::parameters const &param
)
:
	model::object(
		param,
		FCPPT_TEXT("player"),
		z_ordering::model_generic,
		true
	),
	angle_(static_cast<funit>(0)),
	target_angle(angle_)
{
	at(bottom).order(z_ordering::player_lower);
	
	at(top).order(z_ordering::player_upper);
	
	// FIXME: put the rotation point in a config file?
/*	at(top).rotate_around(
		player_body_center);*/
}


void
sanguis::client::draw2d::entities::player::speed(
	vector2 const &v
)
{
	model::object::speed(v);

	if (!is_null(v))
		model::object::orientation(
			*fcppt::math::vector::angle_between<funit>(
				vector2::null(),
				v
			),
			0
		);
}

void
sanguis::client::draw2d::entities::player::orientation(
	sprite::rotation_type const u
)
{
	model::object::orientation(u, 1); // TODO: better interface for this in model
}

void
sanguis::client::draw2d::entities::player::update(
	time_type const time
)
{
	model::object::update(time);

	vector2 const
		leg_center(
			fcppt::math::vector::structure_cast<
				vector2
			>(
				player_leg_center
			)
		),
		body_center(
			fcppt::math::vector::structure_cast<
				vector2
			>(
				player_body_center
			)
		);

	sprite::rotation_type const sprite_rotation = at(bottom).rotation();

	vector2 const new_rotation(
		fcppt::math::point_rotate(
			leg_center,
			vector2(
				static_cast<funit>(at(bottom).w()/2),
				static_cast<funit>(at(bottom).h()/2)
			),
			sprite_rotation
		)
	);

	vector2 const
		rot_abs = fcppt::math::vector::structure_cast<
			vector2
		>(
			at(bottom).pos())+new_rotation,
		top_pos = rot_abs - body_center;

	at(top).pos(
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			top_pos
		)
	);
}
