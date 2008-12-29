#include "generator.hpp"
#include "simple.hpp"
#include <boost/assign/ptr_list_inserter.hpp>

sanguis::server::waves::generator::generator()
{
	boost::assign::ptr_push_back<waves::simple>(waves)
	(
		static_cast<time_type>(0),
		static_cast<time_type>(5),
		50,
		enemy_type::spider
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(1),
		10,
		enemy_type::spider
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(1),
		10,
		enemy_type::skeleton
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(0.7),
		200,
		enemy_type::zombie00
	)(
		static_cast<time_type>(20),
		static_cast<time_type>(1),
		50,
		enemy_type::zombie01
	)(
		static_cast<time_type>(30),
		static_cast<time_type>(0.8),
		30,
		enemy_type::wolf_black
	)(
		static_cast<time_type>(60),
		static_cast<time_type>(2),
		30,
		enemy_type::wolf_white
	)(
		static_cast<time_type>(60),
		static_cast<time_type>(1),
		20,
		enemy_type::wolf_brown
	);
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
