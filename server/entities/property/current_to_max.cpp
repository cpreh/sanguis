#include "current_to_max.hpp"
#include "object.hpp"

void
sanguis::server::entities::property::current_to_max(
	object &object_
)
{
	object_.current(
		object_.max()
	);
}
