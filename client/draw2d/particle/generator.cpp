#include "generator.hpp"
#include "object.hpp"
#include "velocity_from_movement.hpp"
#include "rotation_from_alignment.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::particle::generator::generator(
	generation_callback const generate_object,
	point const &pos,
	time_type const life_time,
	time_type const frequency,
	unsigned const spawn_initial,
	align_type::type const alignment,
	depth_type const depth,
	dispersion_range const &dispersion_value,
	velocity_range const &velocity,
	rotation_velocity_range const &rot_velocity,
	movement_type::type const mt
)
:
	container(
		pos,
		point::null(),
		depth,
		rotation_type(0),
		rotation_type(0)
	),
	generate_object(generate_object),
	frequency_timer(sge::time::second_f(frequency)),
	life_timer(sge::time::second_f(life_time)),
	alignment(alignment),
	dispersion_angle(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	dispersion_value(dispersion_value),
	velocity_angle(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	velocity_value(velocity),
	rot_angle(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	rot_direction(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			static_cast<rotation_type>(1))),
	rot_velocity(rot_velocity),
	movement(mt)
{
	for (unsigned i = 0; i < spawn_initial; ++i)
		generate();
}

void sanguis::client::draw2d::particle::generator::generate()
{
	rotation_type const disp_rot = dispersion_angle();
	point::value_type const disp_value = dispersion_value();

	point const object_pos(
		std::cos(disp_rot)*disp_value,
		std::sin(disp_rot)*disp_value);
	
	point const &diff = object_pos;

	point const refpoint = 
		is_null(diff) 
			? point(
				static_cast<point::value_type>(rot_angle()),
				static_cast<point::value_type>(rot_angle()))
			: diff;
			
	point const velocity(
		particle::velocity_from_movement(
			movement,
			refpoint,
			velocity_angle,
			velocity_value
		)
	);
	
	rotation_type const rot(
		particle::rotation_from_alignment(
			alignment,
			refpoint,
			rot_angle
		)
	);

	base_ptr object = generate_object();

	object->pos(object_pos);
	object->vel(velocity);
	object->rot(rot);
	/*
	object->rot_vel(
		(rot_direction() > sge::su(0.5) 
			? sge::su(-1) 
			: sge::su(1)) * 
				rot_velocity());
	*/
	object->rot_vel(static_cast<rotation_type>(0));
	
	add(object);
}

bool
sanguis::client::draw2d::particle::generator::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d
)
{
	clock.update(delta);

	bool const delete_now = container::update(delta,p,r,d);

	if (!life_timer.expired())
	{
		if (frequency_timer.update_b())
			generate();
		
		return false;
	}

	return delete_now;
}
