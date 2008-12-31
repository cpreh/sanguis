#include "simple.hpp"
#include "spawn.hpp"
#include <sge/time/second_f.hpp>

sanguis::server::waves::simple::simple(
	time_type const delay,
	time_type const spawn_interval,
	unsigned const total_spawn_count,
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
	total_spawn_count(total_spawn_count),
	etype(etype),
	spawn_count(0)
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

	if(spawn_count == total_spawn_count)
		return;
	++spawn_count;

	spawn(
		env,
		etype);
}

bool sanguis::server::waves::simple::ended() const
{
	return spawn_count == total_spawn_count;
}
