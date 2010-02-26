#include "linear_change.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::linear_change(
	base &base_,
	value const &value_
)
{
	base::linear_type linear_(
		base_.linear()
	);

	linear_.change(
		value_
	);

	base_.linear(
		linear_
	);
}
