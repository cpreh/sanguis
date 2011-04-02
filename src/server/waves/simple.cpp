#include "simple.hpp"
#include "spawn.hpp"
#include <sge/time/second_f.hpp>

sanguis::server::waves::simple::simple(
	time_type const _delay,
	time_type const _spawn_interval,
	unsigned const _waves,
	unsigned const _spawns_per_wave,
	enemy_type::type const _etype
)
:
	diff_(),
	delay_timer_(
		sge::time::second_f(
			_delay
		),
		sge::time::activation_state::active,
		diff_.callback()
	),
	spawn_timer_(
		sge::time::second_f(
			_spawn_interval
		),
		sge::time::activation_state::active,
		diff_.callback()
	),
	waves_(_waves),
	spawns_per_wave_(_spawns_per_wave),
	etype_(_etype),
	waves_spawned_(0)
{
}

sanguis::server::waves::simple::~simple()
{
}

void
sanguis::server::waves::simple::process(
	time_type const _diff,
	environment::object &_env,
	environment::load_context &_load_context
)
{
	diff_.update(
		_diff
	);

	if(
		!delay_timer_.expired()
	)
		return;

	if(
		!spawn_timer_.update_b()
	)
		return;

	if(
		waves_spawned_ == waves_
	)
		return;
	
	++waves_spawned_;

	for(
		unsigned i = 0;
		i < spawns_per_wave_;
		++i
	)
		waves::spawn(
			_env,
			_load_context,
			etype_
		);
}

bool
sanguis::server::waves::simple::ended() const
{
	return waves_spawned_ == waves_;
}
