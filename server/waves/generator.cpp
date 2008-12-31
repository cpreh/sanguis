#include "generator.hpp"
#include "simple.hpp"
#include <boost/assign/ptr_list_inserter.hpp>

sanguis::server::waves::generator::generator()
{
	boost::assign::ptr_push_back<waves::simple>(waves)
	(
		static_cast<time_type>(0),
		static_cast<time_type>(2),
		30,
		1,
		enemy_type::spider
	)(
		static_cast<time_type>(0),
		static_cast<time_type>(0),
		50,
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
		static_cast<time_type>(1.5),
		40,
		1,
		enemy_type::zombie00
	)(
		static_cast<time_type>(90),
		static_cast<time_type>(1.5),
		40,
		1,
		enemy_type::zombie01
	)(
		static_cast<time_type>(90),
		static_cast<time_type>(1.5),
		40,
		1,
		enemy_type::zombie00
	)(
		static_cast<time_type>(30),
		static_cast<time_type>(1),
		12,
		1,
		enemy_type::wolf_brown
	)(
		static_cast<time_type>(60),
		static_cast<time_type>(1),
		12,
		1,
		enemy_type::wolf_white
	)(
		static_cast<time_type>(90),
		static_cast<time_type>(1),
		12,
		1,
		enemy_type::wolf_black
	)(
		static_cast<time_type>(160),
		static_cast<time_type>(0),
		40,
		1,
		enemy_type::maggot
	)(
		static_cast<time_type>(180),
		static_cast<time_type>(1),
		2,
		1,
		enemy_type::skeleton
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
