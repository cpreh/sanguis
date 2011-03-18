#include "tick.hpp"

sanguis::client::events::tick::tick(
	time_type const _delta
) 
:
	delta_(_delta) 
{
}

sanguis::time_type
sanguis::client::events::tick::delta() const
{
	return delta_;
}
