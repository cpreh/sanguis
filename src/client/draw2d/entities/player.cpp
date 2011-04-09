#include "player.hpp"
#include "../z_ordering.hpp"
#include "../sprite/index.hpp"
#include "../sprite/point.hpp"
#include <sge/sprite/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/signed_angle_cast.hpp>
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
	model::parameters const &_param
)
:
	model::object(
		_param,
		FCPPT_TEXT("player"),
		z_ordering::model_generic,
		model::needs_healthbar::yes,
		model::decay_option::delayed
	),
	angle_(
		static_cast<
			funit
		>(
			0
		)
	)
{
	this->at(
		bottom
	).order(
		z_ordering::player_lower
	);
	
	this->at(
		top
	).order(
		z_ordering::player_upper
	);
}

sanguis::client::draw2d::entities::player::~player()
{
}

void
sanguis::client::draw2d::entities::player::speed(
	vector2 const &_speed
)
{
	model::object::speed(
		_speed
	);

	if(
		!fcppt::math::vector::is_null(
			_speed
		)
	)
		model::object::orientation(
			fcppt::math::vector::signed_angle_cast<
				funit
			>(
				vector2::null(),
				_speed
			),
			0
		);
}

void
sanguis::client::draw2d::entities::player::orientation(
	sprite::rotation_type const _orientation
)
{
	model::object::orientation(
		_orientation,
		top.get() // TODO
	); // TODO: better interface for this in model
}

void
sanguis::client::draw2d::entities::player::update(
	time_type const _time
)
{
	model::object::update(
		_time
	);

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

	sprite::rotation_type const sprite_rotation(
		this->at(
			bottom
		).rotation()
	);

	vector2 const new_rotation(
		fcppt::math::point_rotate(
			leg_center,
			vector2(
				static_cast<
					funit
				>(
					this->at(
						bottom
					).w()
					/ 2
				),
				static_cast<
					funit
				>(
					this->at(
						bottom
					).h()
					/2
				)
			),
			sprite_rotation
		)
	);

	vector2 const
		rot_abs(
			fcppt::math::vector::structure_cast<
				vector2
			>(
				this->at(
					bottom
				).pos()
			)
			+
			new_rotation
		),
		top_pos(
			rot_abs - body_center
		);

	this->at(
		top
	).pos(
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			top_pos
		)
	);
}
