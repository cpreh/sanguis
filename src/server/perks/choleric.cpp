#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::choleric::choleric(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::perks::perk(
		sanguis::perk_type::choleric
	),
	diff_clock_(
		_diff_clock
	),
	shoot_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::seconds(
				5
			)
		)
	),
	rand_(
		_random_generator,
		sanguis::server::perks::choleric::distribution(
			sanguis::server::perks::choleric::distribution::param_type::min(
				0.f
			),
			sanguis::server::perks::choleric::distribution::param_type::sup(
				fcppt::math::twopi<
					sanguis::server::space_unit
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
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::environment::object &_env
)
{
	if(
		!sge::timer::reset_when_expired(
			shoot_timer_
		)
	)
		return;

	sanguis::server::level const rocket_level(
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
		sanguis::server::direction const direction(
			rand_()
		);

		sanguis::server::environment::insert_no_result(
			_env,
			spawn_bullets
			?
				sanguis::server::entities::unique_ptr(
					fcppt::make_unique_ptr<
						sanguis::server::entities::projectiles::simple_bullet
					>(
						diff_clock_,
						_env.load_context(),
						_entity.team(),
						sanguis::server::damage::unit(
							2.f
						),
						direction
					)
				)
			:
				sanguis::server::entities::unique_ptr(
					fcppt::make_unique_ptr<
						sanguis::server::entities::projectiles::rocket
					>(
						diff_clock_,
						_env.load_context(),
						_entity.team(),
						sanguis::server::damage::unit(
							5.f
						),
						sanguis::server::radius(
							90.f
						),
						direction
					)
				)
			,
			sanguis::server::entities::insert_parameters(
				_entity.center(),
				sanguis::server::angle(
					direction.get()
				)
			)
		);
	}
}

void
sanguis::server::perks::choleric::change(
	sanguis::server::entities::with_perks &,
	sanguis::server::perks::level_diff
)
{
}
