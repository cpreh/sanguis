#include "spawn_pickup.hpp"
#include "environment.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/monster.hpp"
#include "entities/pickups/weapon.hpp"
#include "../random.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>
#include <boost/tr1/random.hpp>
#include <boost/tr1/array.hpp>

void sanguis::server::spawn_pickup(
	pos_type const &pos,
	environment const &env)
{
	// TODO: rework this file!
	// too ugly
	
	typedef std::tr1::uniform_int<
		unsigned
	> uniform_ui;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_ui
	> rng_type;

	unsigned const weapon_pickup_count(3);
	std::tr1::array<
		weapon_type::type,
		weapon_pickup_count
	> const weapon_pickups = {
	{
		weapon_type::pistol,
		weapon_type::rocket_launcher,
		weapon_type::shotgun
	}};

	static rng_type rng(
		create_seeded_randgen(),
		uniform_ui(
			0,
			1 + weapon_pickup_count)  // health, monster + 3 weapons
		);

	unsigned const rand_val(rng());

	if(rand_val < weapon_pickups.size())
	{
		env.insert(
			entities::auto_ptr(
				new entities::pickups::weapon(
					env,
					pos,
					team::players,
					weapon_pickups[rand_val])));
		return;
	}

	// TODO: more non weapon pickups
	switch(rand_val) {
	case weapon_pickup_count:
		env.insert(
			entities::auto_ptr(
				new entities::pickups::health(
					env,
					pos,
					team::players,
					10 // FIXME: which health value to use?
				)
			)
		);
		break;
	case weapon_pickup_count + 1:
		env.insert(
			entities::auto_ptr(
				new entities::pickups::monster(
					env,
					pos,
					team::players,
					enemy_type::skeleton // TODO: nille, create a new enemy
				)
			)
		);
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid random number for pickup generated!"));
	}
}
