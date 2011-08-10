#include "explosion_particle.hpp"
#include "../particle/fade_time_range.hpp"
#include "../particle/object.hpp"
#include "../particle/properties.hpp"
#include "../../../duration.hpp"
#include "../../../load/model/animation/context.hpp"
#include <fcppt/random/uniform.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::particle::base_ptr
sanguis::client::draw2d::entities::explosion_particle(
	sanguis::diff_clock const &_diff_clock,
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

	fcppt::random::uniform<
		sanguis::time_unit
	>
	rng(
		particle::fade_time_range(
			_prop.fade_range().get().min(),
			_prop.fade_range().get().max()
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
				sanguis::duration(
					rng()
				),
				fcppt::ref(
					_particle_system
				)
			)
		);
}
