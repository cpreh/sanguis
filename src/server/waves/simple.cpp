#include <sanguis/server/waves/simple.hpp>
#include <sanguis/server/waves/spawn.hpp>
#include <sge/timer/reset_when_expired.hpp>

sanguis::server::waves::simple::simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	waves::delay const &_delay,
	waves::spawn_interval const &_spawn_interval,
	unsigned const _waves,
	unsigned const _spawns_per_wave,
	enemy_type::type const _etype
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	delay_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_delay.get()
		)
	),
	spawn_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_spawn_interval.get()
		)
	),
	waves_(
		_waves
	),
	spawns_per_wave_(
		_spawns_per_wave
	),
	etype_(
		_etype
	),
	waves_spawned_(
		0u
	)
{
}

sanguis::server::waves::simple::~simple()
{
}

void
sanguis::server::waves::simple::process(
	environment::object &_env,
	environment::load_context &_load_context
)
{
	if(
		!delay_timer_.expired()
	)
		return;

	if(
		!sge::timer::reset_when_expired(
			spawn_timer_
		)
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
			diff_clock_,
			random_generator_,
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
