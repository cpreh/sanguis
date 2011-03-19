#include "explosion.hpp"
#include "generator.hpp"
#include "z_ordering.hpp"
#include "properties.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/minmax_pair_impl.hpp>

sanguis::client::draw2d::particle::explosion::explosion(
	property_map const &_properties,
	callback const &_callback,
	point const &_pos,
	point const &_speed,
	depth_type const _depth,
	rotation_type const _rot,
	rotation_type const _rot_vel
)
:
	container(
		_pos,
		_speed,
		_depth,
		_rot,
		_rot_vel
	)
{
	FCPPT_FOREACH_ENUMERATOR(
		current_type,
		particle_type
	)
	{
		properties const &prop(
			_properties[
				current_type
			]
		);

		base_ptr ptr(
			fcppt::make_auto_ptr<
				particle::generator
			>(
				std::tr1::bind(
					_callback,
					current_type
				),
				point::null(),
				prop.gen_life_time(),
				prop.gen_frequency(),
				prop.spawn_initial(),
				prop.align(),
				particle::z_ordering(
					current_type
				),
				// TODO: make this less explicit (needs to be done in sge)!
				dispersion_range(
					static_cast<
						dispersion_range::value_type
					>(
						prop.dispersion().min()
					),
					static_cast<
						dispersion_range::value_type
					>(
						prop.dispersion().max()
					)
				),
				particle::velocity_range(
					prop.speed().min(),
					prop.speed().max()
				),
				particle::rotation_velocity_range(
					prop.rot_speed().min(),
					prop.rot_speed().max()
				),
				prop.movement()
			)
		);

		this->add(
			ptr
		);
	}
}

sanguis::client::draw2d::particle::explosion::~explosion()
{
}
