#include "spawn_pickup.hpp"
#include "environment.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/weapon.hpp"

#include <cstdlib>

namespace
{

void add_pickup(
	sanguis::server::environment const &,
	sanguis::server::entities::auto_ptr);

sanguis::weapon_type::type
draw_random_weapon();

}

void sanguis::server::spawn_pickup(
	messages::pos_type const &pos,
	environment const &env)
{
	int const rnd = std::rand();

	int const areas = RAND_MAX / pickup_type::size;	

	if(rnd < areas)
		add_pickup(
			env,
			entities::auto_ptr(
				new entities::pickups::health(
				env,
				pos,
				team::players,
				10))); // FIXME: which health value to use?
	else if(rnd < 2 * areas)
		add_pickup(
			env,
			entities::auto_ptr(
				new entities::pickups::weapon(
					env,
					pos,
					team::players,
					draw_random_weapon()
			)));
}

namespace
{

void add_pickup(
	sanguis::server::environment const &env,
	sanguis::server::entities::auto_ptr e)
{
	// TODO: maybe we don't need this?
	env.insert(e);
}

sanguis::weapon_type::type
draw_random_weapon()
{
	// FIXME: use std::tr1
	switch(rand() % 2) {
	case 0:
		return sanguis::weapon_type::pistol;
	default:
		return sanguis::weapon_type::shotgun;
	}
}

}
