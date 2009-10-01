#include "linear_add.hpp"
#include "base.hpp"

void
sanguis::server::entities::property::linear_add(
	base &base_,
	value const &value_
)
{
	base::linear_type linear_(
		base_.linear()
	);

	linear_.add(
		value_
	);

	base_.linear(
		linear_
	);
}
