#include "limited.hpp"
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/assert/pre.hpp>
#include <algorithm>

sanguis::server::entities::spawns::limited::limited(
	sanguis::diff_clock const &_diff_clock,
	enemy_type::type const _enemy_type,
	count_per_wave const _count_per_wave,
	interval const _interval,
	limit const _limit
)
:
	spawn(
		_diff_clock,
		_enemy_type
	),
	count_per_wave_(_count_per_wave),
	delay_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_interval.get()
		)
	),
	spawned_(0),
	limit_(_limit)
{
}

sanguis::server::entities::spawns::limited::~limited()
{
}

void
sanguis::server::entities::spawns::limited::unregister(
	entities::base &
)
{
	FCPPT_ASSERT_PRE(
		spawned_ > 0
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
					size_type
				>(
					limit_.get() - spawned_
				),
				static_cast<
					size_type
				>(
					count_per_wave_.get()
				)
			)
		:
			0;
}

void
sanguis::server::entities::spawns::limited::add_count(
	size_type const _add
)
{
	spawned_ += _add;
}
