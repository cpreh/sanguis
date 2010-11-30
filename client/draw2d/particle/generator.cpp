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
	generation_callback const _generate_object,
	point const &_pos,
	time_type const _life_time,
	time_type const _frequency,
	unsigned const _spawn_initial,
	align_type::type const _alignment,
	depth_type const _depth,
	dispersion_range const &_dispersion_value,
	velocity_range const &_velocity,
	rotation_velocity_range const &_rot_velocity,
	movement_type::type const _movement
)
:
	container(
		_pos,
		point::null(),
		_depth,
		rotation_type(0),
		rotation_type(0)
	),
	clock_(),
	generate_object_(_generate_object),
	frequency_timer_(sge::time::second_f(_frequency)),
	life_timer_(sge::time::second_f(_life_time)),
	alignment_(_alignment),
	dispersion_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	dispersion_value_(_dispersion_value),
	velocity_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	velocity_value_(_velocity),
	rot_angle_(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			fcppt::math::twopi<rotation_type>())),
	rot_direction_(
		fcppt::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			static_cast<rotation_type>(1))),
	rot_velocity_(_rot_velocity),
	movement_(_movement)
{
	for (unsigned i = 0; i < _spawn_initial; ++i)
		generate();
}

void sanguis::client::draw2d::particle::generator::generate()
{
	rotation_type const disp_rot = dispersion_angle_();
	point::value_type const disp_value = dispersion_value_();

	point const object_pos(
		std::cos(disp_rot)*disp_value,
		std::sin(disp_rot)*disp_value);
	
	point const &diff = object_pos;

	point const refpoint = 
		is_null(diff) 
			? point(
				static_cast<point::value_type>(rot_angle_()),
				static_cast<point::value_type>(rot_angle_()))
			: diff;
			
	point const velocity(
		particle::velocity_from_movement(
			movement_,
			refpoint,
			velocity_angle_,
			velocity_value_
		)
	);
	
	rotation_type const rot(
		particle::rotation_from_alignment(
			alignment_,
			refpoint,
			rot_angle_
		)
	);

	base_ptr object = generate_object_();

	object->pos(object_pos);
	object->vel(velocity);
	object->rot(rot);
	/*
	object->rot_vel(
		(rot_direction_() > sge::su(0.5) 
			? sge::su(-1) 
			: sge::su(1)) * 
				rot_velocity_());
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
	clock_.update(delta);

	bool const delete_now = container::update(delta,p,r,d);

	if (!life_timer_.expired())
	{
		if (frequency_timer_.update_b())
			generate();
		
		return false;
	}

	return delete_now;
}
