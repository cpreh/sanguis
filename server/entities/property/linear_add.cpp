#include "linear_add.hpp"
#include "object.hpp"

void
sanguis::server::entities::property::linear_add(
	object &object_,
	value const &value_
)
{
	object::linear_type linear_(
		object_.linear()
	);

	linear_.add(
		value_
	);

	object_.linear(
		linear_
	);
}
