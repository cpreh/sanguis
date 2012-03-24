#include <sanguis/random_generator.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::perks::choleric::choleric(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	perk(
		perk_type::choleric
	),
	diff_clock_(_diff_clock),
	shoot_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
				5
			)
		)
	),
	rand_(
		_random_generator,
		choleric::distribution(
			choleric::distribution::min(
				0.f
			),
			choleric::distribution::sup(
				fcppt::math::twopi<
					server::space_unit
				>()
			)
		)
	)
{
}

sanguis::server::perks::choleric::~choleric()
{
}

void
sanguis::server::perks::choleric::update(
	entities::base &_entity,
	environment::object &_env
)
{
	if(
		!sge::timer::reset_when_expired(
			shoot_timer_
		)
	)
		return;

	server::level const rocket_level(
		10u
	);

	bool const spawn_bullets(
		this->level() < rocket_level
	);

	unsigned const count(
		spawn_bullets
		?
			3 + this->level().get() * 2
		:
			this->level().get()
	);

	for(
		unsigned index = 0;
		index < count;
		++index
	)
	{
		server::direction const direction(
			rand_()
		);

		_env.insert(
			spawn_bullets
			?
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::simple_bullet
					>(
						fcppt::cref(
							diff_clock_
						),
						fcppt::ref(
							_env.load_context()
						),
						_entity.team(),
						damage::unit(
							2.f
						),
						direction
					)
				)
			:
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::rocket
					>(
						fcppt::cref(
							diff_clock_
						),
						fcppt::ref(
							_env.load_context()
						),
						_entity.team(),
						damage::unit(
							5.f
						),
						server::radius(
							1.6f
						),
						direction
					)
				)
			,
			entities::insert_parameters(
				_entity.center(),
				server::angle(
					direction.get()
				)
			)
		);
	}
}

void
sanguis::server::perks::choleric::change(
	entities::base &,
	level_diff
)
{
}
