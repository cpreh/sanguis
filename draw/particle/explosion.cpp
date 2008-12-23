#include "explosion.hpp"
#include "generator.hpp"
#include "z_ordering.hpp"
#include "properties.hpp"
//#include <sge/make_auto_ptr.hpp>
#include <boost/bind.hpp>

sanguis::draw::particle::explosion::explosion(
	properties const &prop,
	callback const callback,
	point const &p,
	point const &s,
	depth_type const d,
	rotation_type const r,
	rotation_type const rv)
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

		base_ptr ptr(
			//sge::make_auto_ptr<
			//	particle::generator
			//>(
			new particle::generator(
				boost::bind(callback, t),
				point::null(),
				prop.gen_life_time,
				prop.gen_frequency,
				prop.spawn_initial,
				prop.align,
				z_ordering(t),
				dispersion_range(
					static_cast<dispersion_range::value_type>(
						prop.dispersion_min),
					static_cast<dispersion_range::value_type>(
						prop.dispersion_max)),
				velocity_range(
					prop.speed_min,
					prop.speed_max),
				rotation_velocity_range(
					prop.rot_speed_min,
					prop.rot_speed_max),
				prop.movement));
		add(ptr);
	}
}
