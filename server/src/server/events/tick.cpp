#include <sanguis/server/events/tick.hpp>

sanguis::server::events::tick::tick(
	sanguis::duration const &_delta
)
:
	delta_(_delta)
{
}

sanguis::duration const &
sanguis::server::events::tick::delta() const
{
	return delta_;
}
