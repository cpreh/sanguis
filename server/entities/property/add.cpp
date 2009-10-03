#include "add.hpp"
#include "changeable.hpp"
#include <algorithm>

void
sanguis::server::entities::property::add(
	changeable &changeable_,
	value const &value_
)
{
	changeable_.current(
		std::min(
			changeable_.max(),
			changeable_.current()
			+ value_
		)
	);
}
