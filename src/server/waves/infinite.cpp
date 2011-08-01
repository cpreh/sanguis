#include "infinite.hpp"
#include "../entities/spawns/limited.hpp"
#include "../entities/insert_parameters_center.hpp"
#include "../environment/object.hpp"
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::waves::infinite::infinite(
	sanguis::diff_clock const &_diff_clock,
	waves::delay const _delay,
	waves::spawn_interval const _spawn_interval,
	waves::spawns_per_wave const _spawns_per_wave,
	enemy_type::type const _etype
)
:
	diff_clock_(_diff_clock),
	delay_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_delay.get()
		)
	),
	spawn_interval_(_spawn_interval),
	spawns_per_wave_(_spawns_per_wave),
	etype_(_etype)
{
}

sanguis::server::waves::infinite::~infinite()
{
}

void
sanguis::server::waves::infinite::process(
	environment::object &_env,
	environment::load_context &
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

		_env.insert(
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::spawns::limited
				>(
					fcppt::cref(
						diff_clock_
					),
					etype_,
					entities::spawns::count_per_wave(
						spawns_per_wave_.get()
					),
					entities::spawns::interval(
						spawn_interval_.get()
					),
					entities::spawns::limit(
						10
					) // TODO!
				)
			),
			entities::insert_parameters_center(
				server::center(
					server::center::value_type::null() // TODO!
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
