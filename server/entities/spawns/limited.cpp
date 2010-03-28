#include "limited.hpp"
#include <fcppt/assert.hpp>
#include <algorithm>

sanguis::server::entities::spawns::limited::limited(
	enemy_type::type const enemy_type_,
	count_per_wave const count_per_wave_,
	interval const interval_,
	limit const limit_
)
:
	spawn(
		enemy_type_
	),
	diff_clock_(),
	count_per_wave_(count_per_wave_),
	delay_(
		interval_,
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	spawned_(0),
	limit_(limit_)
{}

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
	time_type const time_
)
{
	diff_clock_.update(
		time_
	);

	return
		delay_.update_b()
		?
			std::min(
				static_cast<
					size_type
				>(
					limit_ - spawned_
				),
				static_cast<
					size_type
				>(
					count_per_wave_
				)
			)
		:
			0;
}

void
sanguis::server::entities::spawns::limited::add_count(
	size_type const add_
)
{
	spawned_ += add_;	
}
