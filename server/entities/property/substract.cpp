#include "substract.hpp"
#include "changeable.hpp"

void
sanguis::server::entities::property::substract(
	changeable &changeable_,
	value const &value_
)
{
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
}
