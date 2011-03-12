#include "choleric.hpp"
#include "../environment/object.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../entities/projectiles/rocket.hpp"
#include "../entities/insert_parameters.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::perks::choleric::choleric()
:
	perk(
		perk_type::choleric
	),
	clock_(),
	shoot_timer(
		sge::time::second_f(
			5.f
		),
		sge::time::activation_state::active,
		clock_.callback(),
		sge::time::expiration_state::not_expired
	),
	rand(
		fcppt::random::make_inclusive_range(
			static_cast<space_unit>(0),
			fcppt::math::twopi<space_unit>()
		)
	)
{}

void
sanguis::server::perks::choleric::update(
	entities::base &e,
	time_type const time,
	environment::object_ptr const env
)
{
	clock_.update(time);

	if(!shoot_timer.update_b())
		return;

	unsigned const max(
		can_raise_level()
		? 3 + level() * 2
		: 10
	);

	for(
		unsigned i = 0;
		i < max;
		++i
	)
	{
		space_unit const angle(
			rand()
		);

		env->insert(
			can_raise_level()
			?
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::simple_bullet
					>(
						env->load_context(),
						e.team(),
						damage::unit(2), // damage
						angle
					)
				)
			:
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::rocket
					>(
						env->load_context(),
						e.team(),
						damage::unit(5), // damage
						static_cast<space_unit>(80), // aoe
						angle
					)
				)
			,
			entities::insert_parameters(
				e.center(),
				angle
			)
		);
	}
}

sanguis::server::perks::level_type
sanguis::server::perks::choleric::max_level() const
{
	return 10;
}

void
sanguis::server::perks::choleric::change(
	entities::base &,
	level_diff
)
{}