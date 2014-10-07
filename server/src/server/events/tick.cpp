#include <sanguis/duration.hpp>
#include <sanguis/server/slowdown.hpp>
#include <sanguis/server/events/tick.hpp>


sanguis::server::events::tick::tick(
	sanguis::duration const &_delta,
	sanguis::server::slowdown const _slowdown
)
:
	delta_{
		_delta
	},
	slowdown_{
		_slowdown
	}
{
}

sanguis::duration const &
sanguis::server::events::tick::delta() const
{
	return
		delta_;
}

sanguis::server::slowdown const
sanguis::server::events::tick::slowdown() const
{
	return
		slowdown_;
}
