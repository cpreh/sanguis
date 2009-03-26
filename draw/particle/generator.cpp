#include "generator.hpp"
#include "object.hpp"
#include <boost/bind.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/normalize.hpp>
#include <sge/math/vector/arithmetic.hpp>

sanguis::draw::particle::generator::generator(
	generation_callback const generate_object,
	point const &pos,
	time_type const life_time,
	time_type const frequency,
	unsigned const spawn_initial,
	align_type::type alignment,
	depth_type depth,
	dispersion_range const &dispersion_value,
	velocity_range const &velocity,
	rotation_velocity_range const &rot_velocity,
	movement_type::type const mt,
	draw::environment const &e)
:
	container(
		pos,
		point::null(),
		depth,
		rotation_type(0),
		rotation_type(0),
		e),
	generate_object(generate_object),
	frequency_timer(sge::time::second_f(frequency)),
	life_timer(sge::time::second_f(life_time)),
	alignment(alignment),
	dispersion_angle(
		sge::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			sge::math::twopi<rotation_type>())),
	dispersion_value(dispersion_value),
	velocity_angle(
		sge::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			sge::math::twopi<rotation_type>())),
	velocity_value(velocity),
	rot_angle(
		sge::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			sge::math::twopi<rotation_type>())),
	rot_direction(
		sge::random::make_inclusive_range(
			static_cast<rotation_type>(0),
			static_cast<rotation_type>(1))),
	rot_velocity(rot_velocity),
	movement(mt)
{
	for (unsigned i = 0; i < spawn_initial; ++i)
		generate();
}

void sanguis::draw::particle::generator::generate()
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
			
	point velocity = point::null();
	switch (movement)
	{
		case movement_type::random:
		{
			rotation_type const s_angle = velocity_angle();
			velocity = point(std::cos(s_angle),std::sin(s_angle)) * velocity_value();
		}
		break;
		case movement_type::shrinking:
			velocity = normalize(refpoint);
		break;
		case movement_type::expanding:
			velocity = normalize(-refpoint);
		break;
		default:
			throw sge::exception(
				SGE_TEXT("invalid movement type"));
	}
	
	rotation_type rot;
	switch (alignment)
	{
		case align_type::none:
			rot = static_cast<rotation_type>(0);
		break;
		case align_type::to_center:
		{
			rot = *sge::math::angle_to<rotation_type>(point::null(),refpoint);
		}
		break;
		case align_type::random:
			rot = rot_angle();
		break;
		default:
			throw sge::exception(
				SGE_TEXT("invalid align type"));
	}

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

bool sanguis::draw::particle::generator::update(
	time_type const delta,
	point const &p,
	rotation_type const r,
	depth_type const d)
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
