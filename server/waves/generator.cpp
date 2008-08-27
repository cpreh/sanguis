#include "generator.hpp"
#include "simple.hpp"
#include <sge/time/second.hpp>

sanguis::server::waves::generator::generator()
: diff_clock_(),
  wave_timer(
  	sge::time::second(
		static_cast<sge::time::unit>(20)),
	true,
	diff_clock_.callback()),
  wave_counter(0)
{
	// TODO: make this more flexible!
	waves.push_back(
		new waves::simple(
			static_cast<time_type>(0.5),
			200,
			enemy_type::zombie00));
}

void sanguis::server::waves::generator::process(
	time_type const diff,
	environment const &env)
{
	diff_clock_.update(diff);

	if(wave_timer.update_b())
	{
		switch(wave_counter) {
		case 0:
			waves.push_back(
				new waves::simple(
					static_cast<time_type>(1),
					50,
					enemy_type::zombie01));
			break;
		case 1:
			waves.push_back(
				new waves::simple(
					static_cast<time_type>(0.8),
					30,
					enemy_type::wolf_black));
		case 2:
			waves.push_back(
				new waves::simple(
					static_cast<time_type>(2),
					10,
					enemy_type::wolf_white));
		case 3:
			waves.push_back(
				new waves::simple(
					static_cast<time_type>(1),
					20,
					enemy_type::wolf_brown));
		}
		if(wave_counter < 4)
			++wave_counter;
	}

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
