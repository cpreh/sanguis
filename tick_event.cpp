#include "tick_event.hpp"

sanguis::tick_event::tick_event(const time_diff delta_) 
: delta_(delta_) 
{}

sanguis::time_diff sanguis::tick_event::delta() const
{
	return delta_;
}
