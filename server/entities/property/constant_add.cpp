#include "constant_add.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::constant_add(
	base &base_,
	value const &value_
)
{
	base::constant_type constant_(
		base_.constant()
	);

	constant_.add(
		value_
	);

	base_.constant(
		constant_
	);
}
