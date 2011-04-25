#include "limited.hpp"
#include <fcppt/assert.hpp>
#include <algorithm>

sanguis::server::entities::spawns::limited::limited(
	enemy_type::type const _enemy_type,
	count_per_wave const _count_per_wave,
	interval const _interval,
	limit const _limit
)
:
	spawn(
		_enemy_type
	),
	diff_clock_(),
	count_per_wave_(_count_per_wave),
	delay_(
		_interval.get(),
		sge::time::activation_state::active,
		diff_clock_.callback()
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
	FCPPT_ASSERT(
		spawned_ > 0
	);

	--spawned_;
}

sanguis::server::entities::spawns::size_type
sanguis::server::entities::spawns::limited::may_spawn(
	sanguis::time_delta const &_time
)
{
	diff_clock_.update(
		_time
	);

	return
		delay_.update_b()
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
