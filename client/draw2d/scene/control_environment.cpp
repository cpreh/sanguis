#include "control_environment.hpp"
#include "object.hpp"
#include "../entities/base.hpp"
#include <fcppt/math/vector/angle_between.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert.hpp>

sanguis::client::draw2d::scene::control_environment::control_environment(
	object &object_
)
:
	object_(object_)
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
	// FIXME: where to get this from?
}

sanguis::client::control::key_scale
sanguis::client::draw2d::scene::control_environment::rotation() const
{
	fcppt::optional<
		control::direction_vector
	> const ret(
		fcppt::math::vector::angle_between<
			control::key_scale
		>(
			object_.own_player().center(),
			attack_dest()
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
	direction_.x() += x;
}

void
sanguis::client::draw2d::scene::control_environment::direction_y(
	client::control::key_scale const y
)
{
	direction_.y() += y;
}
