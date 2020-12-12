#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_DISTRIBUTION_IMPL_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_DISTRIBUTION_IMPL_HPP_INCLUDED

#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int_distribution_decl.hpp>
#include <sanguis/creator/impl/random/value.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename IntType
>
sanguis::creator::impl::random::uniform_int_distribution<
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
sanguis::creator::impl::random::uniform_int_distribution<
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
sanguis::creator::impl::random::uniform_int_distribution<
	IntType
>::param_type::max() const
{
	return
		max_;
}

template<
	typename IntType
>
sanguis::creator::impl::random::uniform_int_distribution<
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
		sanguis::creator::impl::random::randgen::max()
	);*/
}

template<
	typename IntType
>
typename
sanguis::creator::impl::random::uniform_int_distribution<
	IntType
>::result_type
sanguis::creator::impl::random::uniform_int_distribution<
	IntType
>::operator()(
	sanguis::creator::impl::random::generator &_randgen
)
{
	using
	unsigned_result_type
	=
	std::make_unsigned_t<
		result_type
	>;

	using
	result_common_type
	=
	std::common_type_t<
		sanguis::creator::impl::random::value,
		unsigned_result_type
	>;

	auto const input_range(
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

	auto const rng_range(
		static_cast<
			result_common_type
		>(
			sanguis::creator::impl::random::generator::max()
		)
	);

	if(
		input_range
		==
		rng_range
	)
	{
		return
			static_cast<
				result_type
			>(
				_randgen()
			)
			+
			min_;
	}

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
	{
		result =
			_randgen();
	}

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
