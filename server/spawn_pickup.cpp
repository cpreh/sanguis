#include "spawn_pickup.hpp"
#include "environment.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/weapon.hpp"
#include "../random.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/tr1/random.hpp>
#include <boost/array.hpp>

void sanguis::server::spawn_pickup(
	messages::pos_type const &pos,
	environment const &env)
{
	typedef std::tr1::uniform_int<
		unsigned
	> uniform_ui;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_ui
	> rng_type;

	unsigned const weapon_pickup_count(3);
	boost::array<
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
			0 + weapon_pickup_count)  // health + 3 weapons
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
					10))); // FIXME: which health value to use?
		break;
	default:
		throw sge::exception(
			SGE_TEXT("Invalid random number for pickup generated!"));
	}
}
