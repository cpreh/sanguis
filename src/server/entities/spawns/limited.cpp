#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/difficulty.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/hidden.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::spawns::limited::limited(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::difficulty const _difficulty,
	sanguis::server::entities::spawns::count_per_wave const _count_per_wave,
	sanguis::server::entities::spawns::interval const _interval,
	sanguis::server::entities::spawns::limit const _limit
)
:
	sanguis::server::entities::spawns::spawn(
		_diff_clock,
		_random_generator,
		_enemy_type,
		_difficulty
	),
	sanguis::server::entities::spawns::hidden(),
	count_per_wave_(
		_count_per_wave
	),
	delay_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_interval.get()
		)
	),
	spawned_(
		0u
	),
	limit_(
		_limit
	)
{
}

sanguis::server::entities::spawns::limited::~limited()
{
}

void
sanguis::server::entities::spawns::limited::unregister(
	sanguis::server::entities::base &
)
{
	FCPPT_ASSERT_PRE(
		spawned_ > 0u
	);

	--spawned_;
}

sanguis::server::entities::spawns::size_type
sanguis::server::entities::spawns::limited::may_spawn()
{
	return
		sge::timer::reset_when_expired(
			delay_timer_
		)
		?
			std::min(
				static_cast<
					sanguis::server::entities::spawns::size_type
				>(
					limit_.get() - spawned_
				),
				static_cast<
					sanguis::server::entities::spawns::size_type
				>(
					count_per_wave_.get()
				)
			)
		:
			0u
		;
}

void
sanguis::server::entities::spawns::limited::add_count(
	sanguis::server::entities::spawns::size_type const _add
)
{
	spawned_ += _add;
}
