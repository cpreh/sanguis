#include <sanguis/client/draw2d/entities/model/decay_time.hpp>

sanguis::client::draw2d::entities::model::decay_time::decay_time(
	sanguis::diff_clock const &_diff_clock,
	sanguis::duration const &_duration
)
:
	timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_duration
		)
	)
{
}

sanguis::client::draw2d::entities::model::decay_time::~decay_time()
{
}

bool
sanguis::client::draw2d::entities::model::decay_time::ended() const
{
	return
		timer_.expired();
}
