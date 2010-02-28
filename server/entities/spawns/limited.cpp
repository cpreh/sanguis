#include "limited.hpp"
#include <fcppt/assert.hpp>
#include <algorithm>

sanguis::server::entities::spawns::limited::limited(
	enemy_type::type const enemy_type_,
	count const count_,
	delay const ndelay_,
	limit const limit_
)
:
	spawn(
		enemy_type_
	),
	diff_clock_(),
	count_(count_),
	delay_(
		ndelay_,
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
sanguis::server::entities::spawns::count const
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
			count(
				std::min(
					static_cast<
						limit::value_type
					>(
						spawned_ - limit_
					),
					static_cast<
						count::value_type
					>(
						count_
					)
				)
			)
		:
			count(0);
}
