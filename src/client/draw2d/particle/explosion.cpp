#include <sanguis/client/draw2d/particle/explosion.hpp>
#include <sanguis/client/draw2d/particle/generator.hpp>
#include <sanguis/client/draw2d/particle/properties.hpp>
#include <sanguis/client/draw2d/particle/z_ordering.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/homogenous_pair_impl.hpp>

sanguis::client::draw2d::particle::explosion::explosion(
	sanguis::diff_clock const &_diff_clock,
	particle::property_map const &_properties,
	particle::explosion_callback const &_callback,
	draw2d::center const &_center,
	draw2d::speed const &_speed,
	particle::depth const _depth,
	particle::rotation const _rot,
	particle::rotation_speed const _rot_speed
)
:
	particle::container(
		_diff_clock,
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
					fcppt::cref(
						_diff_clock
					),
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
					prop.dispersion(),
					prop.speed(),
					prop.rot_speed(),
					prop.movement()
				)
			)
		);
	}
}

sanguis::client::draw2d::particle::explosion::~explosion()
{
}
