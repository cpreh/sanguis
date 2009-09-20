#include "generator.hpp"
//#include "simple.hpp"
//#include "infinite.hpp"
#include "debug.hpp"
#include <boost/assign/ptr_list_inserter.hpp>

sanguis::server::waves::generator::generator()
{
	/*
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves)
	(
		delay(60),
		spawn_interval(2),
		count(15),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(0),
		spawn_interval(2),
		count(20),
		spawns_per_wave(2),
		enemy_type::maggot
	)(
		delay(0),
		spawn_interval(1.5f),
		count(40),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(0),
		spawn_interval(2),
		count(60),
		spawns_per_wave(1),
		enemy_type::zombie01
	)(
		delay(90),
		spawn_interval(1),
		count(8),
		spawns_per_wave(2),
		enemy_type::zombie00
	)(
		delay(45),
		spawn_interval(1),
		count(8),
		spawns_per_wave(1),
		enemy_type::wolf_brown
	)(
		delay(80),
		spawn_interval(1),
		count(6),
		spawns_per_wave(2),
		enemy_type::wolf_white
	)(
		delay(120),
		spawn_interval(1),
		count(6),
		spawns_per_wave(2),
		enemy_type::wolf_black
	)(
		delay(130),
		spawn_interval(.5f),
		count(10),
		spawns_per_wave(2),
		enemy_type::spider
	)(
		delay(180),
		spawn_interval(1),
		count(3),
		spawns_per_wave(1),
		enemy_type::skeleton
	);
	*/

	boost::assign::ptr_push_back<waves::debug>(waves)
	();
}

void
sanguis::server::waves::generator::process(
	time_type const diff,
	environment::object_ptr const env,
	environment::load_context_ptr const load_context
)
{
	for(
		wave_list::iterator it = waves.begin();
		it != waves.end();
	)
	{
		it->process(
			diff,
			env,
			load_context
		);

		if(it->ended())
			it = waves.erase(it);
		else
			++it;
	}
}
