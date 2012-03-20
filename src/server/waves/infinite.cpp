#include <sanguis/server/waves/infinite.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::waves::infinite::infinite(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	waves::delay const _delay,
	waves::spawn_interval const _spawn_interval,
	waves::spawns_per_wave const _spawns_per_wave,
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
					fcppt::ref(
						random_generator_
					),
					etype_,
					entities::spawns::count_per_wave(
						spawns_per_wave_.get()
					),
					entities::spawns::interval(
						spawn_interval_.get()
					),
					entities::spawns::limit(
						10u
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
