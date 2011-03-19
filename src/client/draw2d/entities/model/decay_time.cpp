#include "decay_time.hpp"

sanguis::client::draw2d::entities::model::decay_time::decay_time(
	sge::time::duration const &_duration
)
:
	diff_clock_(),
	timer_(
		_duration
	)
{
}

sanguis::client::draw2d::entities::model::decay_time::~decay_time()
{
}

void
sanguis::client::draw2d::entities::model::decay_time::update(
	time_type const _time
)
{
	diff_clock_.update(
		_time
	);
}

bool
sanguis::client::draw2d::entities::model::decay_time::ended() const
{
	return timer_.expired();
}
