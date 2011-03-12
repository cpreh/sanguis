#include "decay_time.hpp"

sanguis::client::draw2d::entities::model::decay_time::decay_time(
	sge::time::duration const &duration_
)
:
	diff_clock_(),
	timer_(
		duration_
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
