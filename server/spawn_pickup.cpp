#include "spawn_pickup.hpp"
#include "environment.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/weapon.hpp"
#include "../random.hpp"
#include <boost/tr1/random.hpp>

namespace
{

void add_pickup(
	sanguis::server::environment const &,
	sanguis::server::entities::auto_ptr);

void add_weapon_pickup(
	sanguis::server::environment const &,
	sanguis::messages::pos_type const &,
	sanguis::weapon_type::type);

}

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

	static rng_type rng(
		create_seeded_randgen(),
		uniform_ui(
			0,
			2  // health + 2 weapons, TODO: maybe calculate this instead of a magic number?
		));

	switch(rng()) {
	case 0:
		add_pickup(
			env,
			entities::auto_ptr(
				new entities::pickups::health(
					env,
					pos,
					team::players,
					10))); // FIXME: which health value to use?
		break;
	case 1:
		add_weapon_pickup(
			env,
			pos,
			weapon_type::pistol);
		break;
	default:
		add_weapon_pickup(
			env,
			pos,
			weapon_type::shotgun);
		break;
	}
}

namespace
{

void add_pickup(
	sanguis::server::environment const &env,
	sanguis::server::entities::auto_ptr e)
{
	env.insert(e);
}

void add_weapon_pickup(
	sanguis::server::environment const &env,
	sanguis::messages::pos_type const &pos,
	sanguis::weapon_type::type const wt)
{
	add_pickup(
		env,
		sanguis::server::entities::auto_ptr(
			new sanguis::server::entities::pickups::weapon(
				env,
				pos,
				sanguis::server::team::players,
				wt
		)));
}

}
