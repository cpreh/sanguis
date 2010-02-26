#include "constant_change.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::constant_change(
	base &base_,
	value const &value_
)
{
	base::constant_type constant_(
		base_.constant()
	);

	constant_.change(
		value_
	);

	base_.constant(
		constant_
	);
}
