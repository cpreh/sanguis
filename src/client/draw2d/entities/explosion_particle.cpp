#include <sanguis/client/draw2d/entities/explosion_particle.hpp>
#include <sanguis/client/draw2d/particle/fade_time_range.hpp>
#include <sanguis/client/draw2d/particle/object.hpp>
#include <sanguis/client/draw2d/particle/properties.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/load/model/animation/context.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion_particle(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_rng,
	particle::particle_type::type const _particle_type,
	sprite::particle::system &_particle_system,
	draw2d::aoe const _aoe,
	particle::properties const &_prop,
	sanguis::load::model::animation::context_ptr _anim
)
{
	if(
		!_prop.fade().get()
	)
		return
			particle::base_ptr(
				fcppt::make_unique_ptr<
					particle::object
				>(
					fcppt::cref(
						_diff_clock
					),
					_particle_type,
					_aoe,
					move(
						_anim
					),
					particle::object::optional_time(),
					fcppt::ref(
						_particle_system
					)
				)
			);

	fcppt::random::variate<
		sanguis::random_generator,
		particle::fade_time_range
	>
	rng(
		_rng,
		particle::fade_time_range(
			particle::fade_time_range::min(
				_prop.fade_range().get().first
			),
			particle::fade_time_range::sup(
				_prop.fade_range().get().second
			)
		)
	);

	return
		particle::base_ptr(
			fcppt::make_unique_ptr<
				particle::object
			>(
				fcppt::cref(
					_diff_clock
				),
				_particle_type,
				_aoe,
				move(
					_anim
				),
				draw2d::particle::object::optional_time(
					sanguis::duration(
						rng()
					)
				),
				fcppt::ref(
					_particle_system
				)
			)
		);
}
