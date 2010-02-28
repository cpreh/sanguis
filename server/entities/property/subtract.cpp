#include "subtract.hpp"
#include "changeable.hpp"

void
sanguis::server::entities::property::subtract(
	changeable &changeable_,
	value const &value_
)
{
	changeable_.current(
		changeable_.current()
		- value_
	);
#if 0
	value const sub(
		changeable_.current()
		- value_
	);

	changeable_.current(
		sub > changeable_.current() 
		?
			0
		:
			sub
	);
#endif
}
