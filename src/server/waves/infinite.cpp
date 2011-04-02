#include "infinite.hpp"
#include "../entities/spawns/limited.hpp"
#include "../entities/insert_parameters_center.hpp"
#include "../environment/object.hpp"
#include <sge/time/second.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::waves::infinite::infinite(
	waves::delay const _delay,
	waves::spawn_interval const _spawn_interval,
	waves::spawns_per_wave const _spawns_per_wave,
	enemy_type::type const _etype
)
:
	diff_clock_(),
	delay_time_(
		sge::time::second(
			_delay.get()
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
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
	time_type const _diff,
	environment::object &_env,
	environment::load_context &
)
{
	// TODO: the waves system must be replaced sometime

	diff_clock_.update(
		_diff
	);

	if(
		delay_time_.update_b()
	)
	{
		delay_time_.deactivate();

		_env.insert(
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::spawns::limited
				>(
					etype_,
					entities::spawns::count_per_wave(
						spawns_per_wave_.get()
					),
					entities::spawns::interval(
						sge::time::second(
							spawn_interval_.get()
						)
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
