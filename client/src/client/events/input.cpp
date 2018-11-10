#include <sanguis/client/events/input.hpp>
#include <sge/input/event_base_fwd.hpp>


sanguis::client::events::input::input(
	sge::input::event_base const &_event
)
:
	event_{
		_event
	}
{
}

sanguis::client::events::input::input(
	input &&
)
= default;

sanguis::client::events::input::input(
	input const &
)
= default;

sanguis::client::events::input &
sanguis::client::events::input::operator=(
	input &&
)
= default;

sanguis::client::events::input &
sanguis::client::events::input::operator=(
	input const &
)
= default;

sanguis::client::events::input::~input()
{
}

sge::input::event_base const &
sanguis::client::events::input::get() const
{
	return
		event_.get();
}
