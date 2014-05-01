#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/spawns/count_per_wave.hpp>
#include <sanguis/server/entities/spawns/interval.hpp>
#include <sanguis/server/entities/spawns/limit.hpp>
#include <sanguis/server/entities/spawns/limited.hpp>
#include <sanguis/server/entities/spawns/total_count.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::spawns::limited::limited(
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::server::world::difficulty const _difficulty,
	sanguis::server::entities::spawns::count_per_wave const _count_per_wave,
	sanguis::server::entities::spawns::interval const _interval,
	sanguis::server::entities::spawns::limit const _limit,
	sanguis::server::entities::spawns::total_count const _total_count
)
:
	sanguis::server::entities::spawns::spawn(
		_random_generator,
		_enemy_type,
		_difficulty
	),
	count_per_wave_(
		_count_per_wave
	),
	delay_timer_(
		sanguis::diff_timer::parameters(
			this->diff_clock(),
			_interval.get()
		)
	),
	alive_(
		0u
	),
	spawned_(
		0u
	),
	limit_(
		_limit
	),
	total_count_(
		_total_count
	)
{
	FCPPT_ASSERT_PRE(
		_limit.get() > 0u
	);

	FCPPT_ASSERT_PRE(
		_count_per_wave.get() > 0u
	);
}

sanguis::server::entities::spawns::limited::~limited()
{
}

bool
sanguis::server::entities::spawns::limited::dead() const
{
	return
		spawned_
		==
		total_count_.get();
}

void
sanguis::server::entities::spawns::limited::unregister(
	sanguis::server::entities::base &
)
{
	FCPPT_ASSERT_PRE(
		alive_ > 0u
	);

	--alive_;
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
				limit_.get() - alive_,
				count_per_wave_.get()
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
	alive_ += _add;

	spawned_ += _add;
}
