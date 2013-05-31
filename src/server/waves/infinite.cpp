#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/waves/delay.hpp>
#include <sanguis/server/waves/infinite.hpp>
#include <sanguis/server/waves/spawn_interval.hpp>
#include <sanguis/server/waves/spawns_per_wave.hpp>
#include <sanguis/server/waves/wave.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::waves::infinite::infinite(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::waves::delay const _delay,
	sanguis::server::waves::spawn_interval const _spawn_interval,
	sanguis::server::waves::spawns_per_wave const _spawns_per_wave,
	sanguis::enemy_type const _etype
)
:
	sanguis::server::waves::wave(),
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
	spawn_interval_(
		_spawn_interval
	),
	spawns_per_wave_(
		_spawns_per_wave
	),
	etype_(
		_etype
	)
{
}

sanguis::server::waves::infinite::~infinite()
{
}

void
sanguis::server::waves::infinite::process(
	sanguis::server::environment::object &_env,
	sanguis::server::environment::load_context &
)
{
	// TODO: the waves system must be replaced sometime

	if(
		sge::timer::reset_when_expired(
			delay_timer_
		)
	)
	{
		delay_timer_.active(
			false
		);

		sanguis::server::environment::insert_no_result(
			_env,
			fcppt::make_unique_ptr<
				sanguis::server::entities::spawns::limited
			>(
				diff_clock_,
				random_generator_,
				etype_,
				sanguis::server::entities::spawns::count_per_wave(
					spawns_per_wave_.get()
				),
				sanguis::server::entities::spawns::interval(
					spawn_interval_.get()
				),
				sanguis::server::entities::spawns::limit(
					10u
				) // TODO!
			),
			sanguis::server::entities::insert_parameters_center(
				sanguis::server::center(
					sanguis::server::center::value_type::null() // TODO!
				)
			)
		);
	}
}

bool
sanguis::server::waves::infinite::ended() const
{
	return false;
}
