#include "explosion.hpp"
#include "generator.hpp"
#include "../settings/object.hpp"
#include "../depth_values.hpp"
#include <boost/bind.hpp>

sanguis::draw::particle::explosion::explosion(
	settings::object const &set,
	callback const callback,
	point const &p,
	point const &s,
	depth_type d,
	rotation_type r,
	rotation_type rv)
:
	container(
		p,
		s,
		d,
		r,
		rv)
{
	for (unsigned mt = 0; mt < particle_type::size; ++mt)
	{
		particle_type::type const t = static_cast<particle_type::type>(mt);
		settings::model const &curmodel = set.model(t);

		base_ptr ptr(
			new particle::generator(
				boost::bind(callback,t),
				point::null(),
				curmodel.gen_life_time,
				curmodel.gen_frequency,
				curmodel.spawn_initial,
				curmodel.align,
				depth_values::from_model(t),
				dispersion_range(
					static_cast<dispersion_range::value_type>(
						curmodel.dispersion_min),
					static_cast<dispersion_range::value_type>(
						curmodel.dispersion_max)),
				velocity_range(
					curmodel.speed_min,
					curmodel.speed_max),
				rotation_velocity_range(
					curmodel.rot_speed_min,
					curmodel.rot_speed_max),
				curmodel.movement));
		add(ptr);
	}
}
