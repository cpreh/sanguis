#include "tick.hpp"

sanguis::client::events::tick::tick(
	sanguis::time_delta const &_delta
) 
:
	delta_(_delta) 
{
}

sanguis::time_delta const &
sanguis::client::events::tick::delta() const
{
	return delta_;
}
