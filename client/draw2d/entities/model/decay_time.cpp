#include "decay_time.hpp"
#include <sge/time/second.hpp>

sanguis::client::draw2d::entities::model::decay_time::decay_time()
:
	diff_clock_(),
	timer_(
		sge::time::second(
			120
		)
	)
{}

void
sanguis::client::draw2d::entities::model::decay_time::update(
	time_type const time_
)
{
	diff_clock_.update(
		time_
	);
}

bool
sanguis::client::draw2d::entities::model::decay_time::ended() const
{
	return timer_.expired();
}
