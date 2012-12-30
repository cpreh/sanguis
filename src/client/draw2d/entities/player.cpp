#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
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
		fcppt::assign::make_container<
			entities::order_vector
		>(
			z_ordering::player_lower
		)(
			z_ordering::player_upper
		),
		model::needs_healthbar::yes,
		model::decay_option::delayed
	)
{
}

sanguis::client::draw2d::entities::player::~player()
{
}

void
sanguis::client::draw2d::entities::player::speed(
	draw2d::speed const &_speed
)
{
	model::object::speed(
		_speed
	);

	if(
		this->walking()
	)
		model::object::orientation(
			fcppt::math::vector::signed_angle_between_cast<
				sanguis::client::draw2d::funit
			>(
				vector2::null(),
				_speed.get()
			),
			bottom
		);
}

void
sanguis::client::draw2d::entities::player::orientation(
	sprite::rotation const _orientation
)
{
	model::object::orientation(
		_orientation,
		top // TODO
	); // TODO: better interface for this in model
}

void
sanguis::client::draw2d::entities::player::update()
{
	model::object::update();

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

	sprite::rotation const sprite_rotation(
		this->at(
			bottom
		).rotation()
	);

	vector2 const new_rotation(
		fcppt::math::point_rotate(
			leg_center,
			vector2(
				static_cast<
					sanguis::client::draw2d::funit
				>(
					this->at(
						bottom
					).w()
					/ 2
				),
				static_cast<
					sanguis::client::draw2d::funit
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
