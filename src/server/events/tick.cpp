#include "tick.hpp"

sanguis::server::events::tick::tick(
	time_type const _delta
) 
:
	delta_(_delta) 
{
}

sanguis::time_type
sanguis::server::events::tick::delta() const
{
	return delta_;
}
