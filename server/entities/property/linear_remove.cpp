#include "linear_remove.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::linear_remove(
	base &base_,
	value const &value_
)
{
	base::linear_type linear_(
		base_.linear()
	);

	linear_.remove(
		value_
	);

	base_.linear(
		linear_
	);
}
