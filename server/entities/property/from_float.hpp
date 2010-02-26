#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_FROM_FLOAT_HPP_INCLUDED

#include "value.hpp"
#include "../../../exception.hpp"
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <cmath>

#include <iostream>

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
	if(
		fcppt::math::almost_zero(
			float_
		)
	)
		return
			value(
				0,
				1
			);
	int exp;

	Float const frac(
		std::frexp(
			float_,
			&exp
		)
	);

	Float const
		dexp(
			std::pow(
				static_cast<Float>(2),
				std::abs(
					exp
				)
			)
		),
		pot(
			std::pow(
				static_cast<Float>(10),
				std::abs(
					exp
				)
			)
		),
		num_exp(
			exp > 0
			?
				dexp
			:
				1
		),
		den_exp(
			exp < 0
			?
				dexp
			:
				1
		);

	value::int_type const
		num(
			static_cast<
				value::int_type
			>(
				num_exp * frac * pot
			)
		),
		den(
			static_cast<
				value::int_type
			>(
				den_exp * pot
			)
		);
	
	std::cerr << "dexp: " << dexp <<  ", pot: " << pot << ", float_: " << float_ <<  ", frac: " << frac << ", exp: " << exp << ", num: " << num << ", den: " << den << '\n';

	if(
		den <= 0
	)
		throw exception(
			(
				fcppt::format(
					FCPPT_TEXT("from_float: den is <= 0 (%1%)")
				)
				% den
			).str()
		);

	return value(
		num,
		den
	);

}

}
}
}
}

#endif
