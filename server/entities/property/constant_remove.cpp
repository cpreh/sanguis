#include "constant_remove.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::constant_remove(
	base &base_,
	value const &value_
)
{
	base::constant_type constant_(
		base_.constant()
	);

	constant_.remove(
		value_
	);

	base_.constant(
		constant_
	);
}
