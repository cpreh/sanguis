#include "generator.hpp"
#include "simple.hpp"

sanguis::server::waves::generator::generator()
{
	// TODO: make this more flexible!
	waves.push_back(
		new waves::simple(
			static_cast<time_type>(0.5),
			100,
			enemy_type::zombie00));
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
