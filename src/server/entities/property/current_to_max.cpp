#include "current_to_max.hpp"
#include "changeable.hpp"

void
sanguis::server::entities::property::current_to_max(
	changeable &changeable_
)
{
	changeable_.current(
		changeable_.max()
	);
}
