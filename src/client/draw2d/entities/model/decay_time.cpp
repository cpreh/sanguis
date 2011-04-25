#include "decay_time.hpp"
#include "../../../../time_to_second.hpp"
#include <sge/time/second_f.hpp>

sanguis::client::draw2d::entities::model::decay_time::decay_time(
	sanguis::time_delta const &_duration
)
:
	diff_clock_(),
	timer_(
		sge::time::second_f(
			sanguis::time_to_second(
				_duration
			)
		)
	)
{
}

sanguis::client::draw2d::entities::model::decay_time::~decay_time()
{
}

void
sanguis::client::draw2d::entities::model::decay_time::update(
	sanguis::time_delta const _time
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
