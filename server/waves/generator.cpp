#include "generator.hpp"
//#include "simple.hpp"
#include "infinite.hpp"
//#include "debug.hpp"
#include <boost/assign/ptr_list_inserter.hpp>

sanguis::server::waves::generator::generator()
{
	// TODO: somehow put this in a configuration file!
	boost::assign::ptr_push_back<waves::infinite>(waves)
	(
		static_cast<time_type>(60),
		static_cast<time_type>(2),
		15,
		2,
		enemy_type::spider
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(1),
		20,
		1,
		enemy_type::maggot
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(1.5),
		40,
		1,
		enemy_type::zombie01
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(2),
		60,
		1,
		enemy_type::zombie01
	)(
		static_cast<time_type>(90),
		static_cast<time_type>(1),
		8,
		2,
		enemy_type::zombie00
	)(
		static_cast<time_type>(45),
		static_cast<time_type>(1),
		8,
		1,
		enemy_type::wolf_brown
	)(
		static_cast<time_type>(80),
		static_cast<time_type>(1),
		6,
		2,
		enemy_type::wolf_white
	)(
		static_cast<time_type>(120),
		static_cast<time_type>(1),
		6,
		2,
		enemy_type::wolf_black
	)(
		static_cast<time_type>(130),
		static_cast<time_type>(.5),
		10,
		2,
		enemy_type::spider
	)(
		static_cast<time_type>(180),
		static_cast<time_type>(1),
		3,
		1,
		enemy_type::skeleton
	);

//	boost::assign::ptr_push_back<waves::debug>(waves)
//	();
}

void sanguis::server::waves::generator::process(
	time_type const diff,
	environment const &env)
{
	for(wave_list::iterator it = waves.begin(); it != waves.end(); )
	{
		it->process(
			diff,
			env);
		if(it->ended())
			it = waves.erase(it);
		else
			++it;
	}
}
