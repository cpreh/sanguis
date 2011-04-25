#include "tick.hpp"

sanguis::server::events::tick::tick(
	sanguis::time_delta const &_delta
) 
:
	delta_(_delta) 
{
}

sanguis::time_delta const &
sanguis::server::events::tick::delta() const
{
	return delta_;
}
