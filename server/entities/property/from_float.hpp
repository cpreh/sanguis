#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED

#include "value.hpp"
#include "../../../exception.hpp"
#include <sge/text.hpp>
#include <cstdlib>
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

	if(
		frac < 0.0
	)
		throw exception(
			SGE_TEXT("Tried to convert a negative floating point number into a rational!")
		);

	value::int_type const
		factor(
			1000
		),
		power(
			1 << std::abs(exp)
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
		* (
			(exp > 0)
			?
				power
			:
				1
		),
		factor
		* (
			(exp < 0)
			?
				power
			:
				1
		)
	);

}

}
}
}
}

#endif
