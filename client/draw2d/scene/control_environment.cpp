#include "control_environment.hpp"
#include "object.hpp"
#include "../entities/base.hpp"
#include "../screen_to_virtual.hpp"
#include "../../control/axis_direction_max.hpp"
#include "../../control/axis_direction_min.hpp"
#include "../../cursor/object.hpp"
#include <fcppt/math/vector/angle_between.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert.hpp>

sanguis::client::draw2d::scene::control_environment::control_environment(
	object &object_,
	client::cursor::object_ptr const cursor_
)
:
	object_(object_),
	cursor_(cursor_),
	direction_(
		client::control::direction_vector::null()
	)
{}

sanguis::client::draw2d::scene::control_environment::~control_environment()
{}

sanguis::client::control::direction_vector const 
sanguis::client::draw2d::scene::control_environment::direction() const
{
	return direction_;
}

sanguis::client::control::direction_vector const
sanguis::client::draw2d::scene::control_environment::attack_dest() const
{
	return
		screen_to_virtual(
			object_.screen_size(),
			-
			fcppt::math::dim::structure_cast<
				sprite::point
			>(
				object_.screen_size() / 2u
			)
			+ object_.player_center()
			+ cursor_->pos()
		);
}

sanguis::client::control::key_scale
sanguis::client::draw2d::scene::control_environment::rotation() const
{
	// TODO: this should not be here
	fcppt::optional<
		control::key_scale
	> const ret(
		fcppt::math::vector::angle_between<
			control::key_scale
		>(
			fcppt::math::dim::structure_cast<
				sprite::point
			>(
				object_.screen_size() / 2u
			),
			cursor_->pos()
		)
	);

	FCPPT_ASSERT(ret);

	return *ret;
}

void
sanguis::client::draw2d::scene::control_environment::direction_x(
	client::control::key_scale const x
)
{
	update_direction(
		direction_.x(),
		x
	);
}

void
sanguis::client::draw2d::scene::control_environment::direction_y(
	client::control::key_scale const y
)
{
	update_direction(
		direction_.y(),
		y
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
