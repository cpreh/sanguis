#include "simple.hpp"
#include "spawn.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>

sanguis::server::waves::simple::simple(
	time_type const delay,
	time_type const spawn_interval,
	unsigned const waves,
	unsigned const spawns_per_wave,
	enemy_type::type const etype)
:
	diff_(),
	delay_timer(
		sge::time::second_f(
			delay),
		true,
		diff_.callback()),
	spawn_timer(
		sge::time::second_f(
			spawn_interval),
		true,
		diff_.callback()),
	waves(waves),
	spawns_per_wave(spawns_per_wave),
	etype(etype),
	waves_spawned(0)
{}

void sanguis::server::waves::simple::process(
	time_type const diff,
	environment const &env)
{
	diff_.update(diff);

	if(!delay_timer.expired())
		return;

	if(!spawn_timer.update_b())
		return;

	if(waves_spawned == waves)
		return;
	
	++waves_spawned;

	for(unsigned i = 0; i < spawns_per_wave; ++i)
		spawn(
			env,
			etype);
}

bool sanguis::server::waves::simple::ended() const
{
	return waves_spawned == waves;
}
