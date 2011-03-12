#include "tick_event.hpp"

sanguis::tick_event::tick_event(
	time_type const _delta
) 
:
	delta_(_delta) 
{}

sanguis::time_type
sanguis::tick_event::delta() const
{
	return delta_;
}
