#include "choleric.hpp"
#include "../environment.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../entities/projectiles/rocket.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/math/pi.hpp>

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
		sge::random::make_inclusive_range(
			static_cast<space_unit>(0),
			sge::math::twopi<space_unit>()
		)
	),
	damage(
		static_cast<space_unit>(1)
	)
{}

void
sanguis::server::perks::choleric::do_apply(
	entities::entity &e,
	time_type const time,
	environment const &env)
{
	clock_.update(time);

	if(!shoot_timer.update_b())
		return;

	for(unsigned i = 0; i < 3 + level() * 2; ++i)
		env.insert(
			can_raise_level()
			?
				entities::auto_ptr(
					new entities::projectiles::simple_bullet(
						env,
						e.center(),
						rand(),
						e.team(),
						damage
					)
				)
			:
				entities::auto_ptr(
					new entities::projectiles::rocket(
						env,
						e.center(),
						rand(),
						e.team(),
						damage,
						static_cast<
							space_unit
						>(
							30
						)
					)
				)
		);
}

bool
sanguis::server::perks::choleric::can_raise_level() const
{
	return level() < 10;
}
