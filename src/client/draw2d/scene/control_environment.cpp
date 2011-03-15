#include "control_environment.hpp"
#include "object.hpp"
#include "../entities/base.hpp"
#include "../screen_to_virtual.hpp"
#include "../../control/axis_direction_max.hpp"
#include "../../control/axis_direction_min.hpp"
#include "../../cursor/object.hpp"
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/signed_angle_cast.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::client::draw2d::scene::control_environment::control_environment(
	object &_object,
	client::cursor::object &_cursor
)
:
	object_(_object),
	cursor_(_cursor),
	direction_(
		client::control::direction_vector::null()
	)
{
}

sanguis::client::draw2d::scene::control_environment::~control_environment()
{
}

sanguis::client::control::direction_vector const 
sanguis::client::draw2d::scene::control_environment::direction() const
{
	return direction_;
}

sanguis::client::control::direction_vector const
sanguis::client::draw2d::scene::control_environment::attack_dest() const
{
	return
		draw2d::screen_to_virtual(
			object_.screen_size(),
			-
			fcppt::math::dim::structure_cast<
				sprite::point
			>(
				object_.screen_size() / 2u
			)
			+ object_.player_center()
			+ cursor_.position()
		);
}

sanguis::client::control::key_scale
sanguis::client::draw2d::scene::control_environment::rotation() const
{
	sprite::point const refpoint(
		fcppt::math::dim::structure_cast<
			sprite::point
		>(
			object_.screen_size() / 2u
		)
	);

	return
		cursor_.position() == refpoint
		?
			// FIXME: this should not update the rotation at all!
			static_cast<control::key_scale>(0)
		:
			fcppt::math::vector::signed_angle_cast<
				control::key_scale
			>(
				refpoint,
				cursor_.position()
			);
}

void
sanguis::client::draw2d::scene::control_environment::direction_x(
	client::control::key_scale const _x
)
{
	this->update_direction(
		direction_.x(),
		_x
	);
}

void
sanguis::client::draw2d::scene::control_environment::direction_y(
	client::control::key_scale const _y
)
{
	this->update_direction(
		direction_.y(),
		_y
	);
}

void
sanguis::client::draw2d::scene::control_environment::update_direction(
	client::control::key_scale &_ref,
	client::control::key_scale const _diff
)
{
	_ref =
		fcppt::math::clamp(
			_ref + _diff,
			static_cast<
				client::control::key_scale
			>(
				control::axis_direction_min()
			),
			static_cast<
				client::control::key_scale
			>(
				control::axis_direction_max()
			)
		);
}
