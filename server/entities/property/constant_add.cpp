#include "constant_add.hpp"
#include "object.hpp"

void
sanguis::server::entities::property::constant_add(
	object &object_,
	value const &value_
)
{
	object::constant_type constant_(
		object_.constant()
	);

	constant_.add(
		value_
	);

	object_.constant(
		constant_
	);
}
