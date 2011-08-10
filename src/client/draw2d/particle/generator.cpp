#include "generator.hpp"
#include "object.hpp"
#include "rotation_from_alignment.hpp"
#include "velocity_from_movement.hpp"
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/unit_circle.hpp>
#include <fcppt/minmax_pair_impl.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::generator::generator(
	sanguis::diff_clock const &_diff_clock,
	particle::generation_callback const _generate_object,
	draw2d::center const &_center,
	particle::gen_life_time const &_life_time,
	particle::gen_frequency const &_frequency,
	particle::spawn_initial const _spawn_initial,
	particle::align_type::type const _alignment,
	particle::depth const _depth,
	particle::dispersion_range const &_dispersion_value,
	particle::speed_range const &_velocity,
	particle::rot_speed_range const &_rot_velocity,
	particle::movement_type::type const _movement
)
:
	particle::container(
		_diff_clock,
		_center,
		draw2d::speed(
			draw2d::speed::value_type::null()
		),
		_depth,
		particle::rotation(
			0
		),
		particle::rotation_speed(
			0
		)
	),
	generate_object_(
		_generate_object
	),
	frequency_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_frequency.get()
		)
	),
	life_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_life_time.get()
		)
	),
	alignment_(
		_alignment
	),
	dispersion_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<
				particle::rotation::value_type
			>(
				0
			),
			fcppt::math::twopi<
				particle::rotation::value_type
			>()
		)
	),
	dispersion_value_(
		fcppt::random::make_inclusive_range(
			_dispersion_value.get().min(),
			_dispersion_value.get().max()
		)
	),
	velocity_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<
				particle::rotation::value_type
			>(
				0
			),
			fcppt::math::twopi<
				particle::rotation::value_type
			>()
		)
	),
	velocity_value_(
		fcppt::random::make_inclusive_range(
			_velocity.get().min(),
			_velocity.get().max()
		)
	),
	rot_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<
				particle::rotation::value_type
			>(
				0
			),
			fcppt::math::twopi<
				particle::rotation::value_type
			>()
		)
	),
	rot_direction_(
		fcppt::random::make_inclusive_range(
			static_cast<
				particle::rotation::value_type
			>(
				0
			),
			static_cast<
				particle::rotation::value_type
			>(
				1
			)
		)
	),
	rot_velocity_(
		fcppt::random::make_inclusive_range(
			_rot_velocity.get().min(),
			_rot_velocity.get().max()
		)
	),
	movement_(
		_movement
	)
{
	for(
		spawn_initial index(
			0
		);
		index < _spawn_initial;
		++index
	)
		this->generate();
}

sanguis::client::draw2d::particle::generator::~generator()
{
}

void
sanguis::client::draw2d::particle::generator::generate()
{
	particle::rotation const disp_rot(
		dispersion_angle_()
	);

	draw2d::funit const disp_value(
		dispersion_value_()
	);

	draw2d::center const object_pos(
		fcppt::math::vector::unit_circle(
			disp_rot.get()
		)
		* disp_value
	);

	draw2d::center const refpoint(
		fcppt::math::vector::is_null(
			object_pos.get()
		)
		?
			draw2d::center(
				draw2d::center::value_type(
					rot_angle_(),
					rot_angle_()
				)
			)
		:
			object_pos
	);

	draw2d::speed const velocity(
		particle::velocity_from_movement(
			movement_,
			refpoint,
			velocity_angle_,
			velocity_value_
		)
	);

	base_ptr object(
		generate_object_()
	);

	object->center(
		object_pos
	);

	object->speed(
		velocity
	);

	object->rot(
		particle::rotation_from_alignment(
			alignment_,
			refpoint,
			rot_angle_
		)
	);

	object->rot_speed(
		particle::rotation_speed(
			0
		)
	);

	this->add(
		move(
			object
		)
	);
}

bool
sanguis::client::draw2d::particle::generator::update(
	draw2d::center const &_pos,
	particle::rotation const _rot,
	particle::depth const _depth
)
{
	bool const delete_now(
		container::update(
			_pos,
			_rot,
			_depth
		)
	);

	if(
		!life_timer_.expired()
	)
	{
		if(
			sge::timer::reset_when_expired(
				frequency_timer_
			)
		)
			this->generate();

		return false;
	}

	return delete_now;
}
