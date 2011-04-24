#include "generator.hpp"
#include "object.hpp"
#include "rotation_from_alignment.hpp"
#include "velocity_from_movement.hpp"
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/unit_circle.hpp>
#include <sge/time/second_f.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::generator::generator(
	particle::generation_callback const _generate_object,
	draw2d::center const &_center,
	sanguis::time_type const _life_time,
	sanguis::time_type const _frequency,
	unsigned const _spawn_initial,
	particle::align_type::type const _alignment,
	particle::depth const _depth,
	particle::dispersion_range const &_dispersion_value,
	particle::velocity_range const &_velocity,
	particle::rotation_velocity_range const &_rot_velocity,
	particle::movement_type::type const _movement
)
:
	particle::container(
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
	clock_(),
	generate_object_(
		_generate_object
	),
	frequency_timer_(
		sge::time::second_f(
			_frequency
		)
	),
	life_timer_(
		sge::time::second_f(
			_life_time
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
		_dispersion_value
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
		_velocity
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
		_rot_velocity
	),
	movement_(
		_movement
	)
{
	for(
		unsigned i = 0;
		i < _spawn_initial;
		++i
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
	
	/*
	object->rot_vel(
		(rot_direction_() > sge::su(0.5) 
			? sge::su(-1) 
			: sge::su(1)) * 
				rot_velocity_());
	*/
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
	sanguis::time_type const _delta,
	draw2d::center const &_pos,
	particle::rotation const _rot,
	particle::depth const _depth
)
{
	clock_.update(
		_delta
	);

	bool const delete_now(
		container::update(
			_delta,
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
			frequency_timer_.update_b()
		)
			this->generate();
		
		return false;
	}

	return delete_now;
}
