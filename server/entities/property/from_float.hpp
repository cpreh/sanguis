#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED

#include "value.hpp"
#include <math.h> // TODO: check if we have frexp!

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{
template<
	typename Float
>
value const
from_float(
	Float const float_
)
{
	int exp;

	double const frac(
		frexp(
			float_,
			&exp
		)
	);

	value::int_type const
		factor(
			1000
		),
		power(
			1 << exp
		);

	return value(
		static_cast<
			value::int_type
		>(
			frac
			* static_cast<
				Float
			>(
				factor
			)
		)
		* power,
		factor * power
	);

}

}
}
}
}

#endif
