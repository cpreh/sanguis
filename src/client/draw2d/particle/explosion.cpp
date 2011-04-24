#include "explosion.hpp"
#include "generator.hpp"
#include "properties.hpp"
#include "z_ordering.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/minmax_pair_impl.hpp>

sanguis::client::draw2d::particle::explosion::explosion(
	particle::property_map const &_properties,
	explosion::callback const &_callback,
	draw2d::center const &_center,
	draw2d::speed const &_speed,
	particle::depth const _depth,
	particle::rotation const _rot,
	particle::rotation_speed const _rot_speed
)
:
	particle::container(
		_center,
		_speed,
		_depth,
		_rot,
		_rot_speed
	)
{
	FCPPT_FOREACH_ENUMERATOR(
		current_type,
		particle::particle_type
	)
	{
		particle::properties const &prop(
			_properties[
				current_type
			]
		);

		this->add(
			particle::base_ptr(
				fcppt::make_unique_ptr<
					particle::generator
				>(
					std::tr1::bind(
						_callback,
						current_type
					),
					draw2d::center(
						draw2d::center::value_type::null()
					),
					prop.gen_life_time(),
					prop.gen_frequency(),
					prop.spawn_initial(),
					prop.align(),
					particle::depth(
						particle::z_ordering(
							current_type
						)
					),
					// TODO: make this less explicit (needs to be done in sge)!
					particle::dispersion_range(
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
			)
		);
	}
}

sanguis::client::draw2d::particle::explosion::~explosion()
{
}
