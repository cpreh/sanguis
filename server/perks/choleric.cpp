#include "choleric.hpp"
#include "../environment/object.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../entities/projectiles/rocket.hpp"
#include "../entities/insert_parameters.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/random/inclusive_range.hpp>
#include <sge/math/twopi.hpp>

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
	)
{}

void
sanguis::server::perks::choleric::do_apply(
	entities::entity &e,
	time_type const time,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context_
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

	for(unsigned i = 0; i < max; ++i)
		env->insert(
			can_raise_level()
			?
				entities::auto_ptr(
					new entities::projectiles::simple_bullet(
						load_context_,
						e.team(),
						static_cast<space_unit>(2) // damage
					)
				)
			:
				entities::auto_ptr(
					new entities::projectiles::rocket(
						load_context_,
						e.team(),
						static_cast<space_unit>(5), // damage
						static_cast<space_unit>(80) // aoe
					)
				)
			,
			entities::insert_parameters(
				e.center(),
				rand()
			)
		);
}

bool
sanguis::server::perks::choleric::can_raise_level() const
{
	return level() < 10;
}
