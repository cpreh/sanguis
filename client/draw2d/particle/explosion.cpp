#include "explosion.hpp"
#include "generator.hpp"
#include "z_ordering.hpp"
#include "properties.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/minmax_pair_impl.hpp>

sanguis::client::draw2d::particle::explosion::explosion(
	property_map const &properties_,
	callback const &callback_,
	point const &p,
	point const &s,
	depth_type const d,
	rotation_type const r,
	rotation_type const rv
)
:
	container(
		p,
		s,
		d,
		r,
		rv
	)
{
	for (unsigned mt = 0; mt < particle_type::size; ++mt)
	{
		particle_type::type const t = static_cast<particle_type::type>(mt);

		properties const &prop(
			properties_[t]
		);

		base_ptr ptr(
			fcppt::make_auto_ptr<
				particle::generator
			>(
				std::tr1::bind(
					callback_,
					t
				),
				point::null(),
				prop.gen_life_time(),
				prop.gen_frequency(),
				prop.spawn_initial(),
				prop.align(),
				z_ordering(t),
				// TODO: make this less explicit (needs to be done in sge)!
				dispersion_range(
					static_cast<dispersion_range::value_type>(
						prop.dispersion().min()),
					static_cast<dispersion_range::value_type>(
						prop.dispersion().max())),
				velocity_range(
					prop.speed().min(),
					prop.speed().max()),
				rotation_velocity_range(
					prop.rot_speed().min(),
					prop.rot_speed().max()),
				prop.movement()
			)
		);

		add(ptr);
	}
}
