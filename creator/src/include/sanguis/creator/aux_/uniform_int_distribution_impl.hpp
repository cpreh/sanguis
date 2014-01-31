#ifndef SANGUIS_CREATOR_AUX__UNIFORM_INT_DISTRIBUTION_IMPL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__UNIFORM_INT_DISTRIBUTION_IMPL_HPP_INCLUDED

#include <sanguis/creator/aux_/uniform_int_distribution_decl.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/rand_value.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename IntType
>
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::param_type::param_type(
	IntType const _min,
	IntType const _max
)
:
	min_(
		_min
	),
	max_(
		_max
	)
{
	FCPPT_ASSERT_PRE(
		min_
		<=
		max_
	);
}

template<
	typename IntType
>
IntType
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::param_type::min() const
{
	return
		min_;
}

template<
	typename IntType
>
IntType
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::param_type::max() const
{
	return
		max_;
}

template<
	typename IntType
>
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::uniform_int_distribution(
	param_type const &_params
)
:
	min_(
		_params.min()
	),
	max_(
		_params.max()
	)
{
/*
	FCPPT_ASSERT_PRE(
		max_
		<=
		sanguis::creator::aux_::randgen::max()
	);*/
}

template<
	typename IntType
>
typename
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::result_type
sanguis::creator::aux_::uniform_int_distribution<
	IntType
>::operator()(
	sanguis::creator::aux_::randgen &_randgen
)
{
	typedef
	typename
	std::make_unsigned<
		result_type
	>::type
	unsigned_result_type;

	typedef
	typename
	std::common_type<
		sanguis::creator::aux_::rand_value,
		unsigned_result_type
	>::type
	result_common_type;

	result_common_type const input_range(
		static_cast<
			result_common_type
		>(
			max_
		)
		-
		static_cast<
			result_common_type
		>(
			min_
		)
	);

	result_common_type const rng_range(
		static_cast<
			result_common_type
		>(
			_randgen.max()
		)
	);

	if(
		input_range
		==
		rng_range
	)
		return
			static_cast<
				result_type
			>(
				_randgen()
			)
			+
			min_;

	result_common_type const extended_input_range(
		input_range
		+
		1
	);

	result_common_type const scaling(
		rng_range
		/
		extended_input_range
	);

	result_common_type const to_discard(
		extended_input_range
		*
		scaling
	);

	result_common_type result(
		to_discard
	);

	while(
		result
		>=
		to_discard
	)
		result =
			_randgen();

	return
		static_cast<
			result_type
		>(
			result
			/
			scaling
		)
		+
		min_;
}

#endif
