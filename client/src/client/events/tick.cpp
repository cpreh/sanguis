#include <sanguis/duration.hpp>
#include <sanguis/client/events/tick.hpp>


sanguis::client::events::tick::tick(
	sanguis::duration const &_delta
)
:
	delta_(
		_delta
	)
{
}

sanguis::duration const &
sanguis::client::events::tick::delta() const
{
	return delta_;
}
