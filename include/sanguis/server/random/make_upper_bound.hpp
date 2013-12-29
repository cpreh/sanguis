#ifndef SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MAKE_UPPER_BOUND_HPP_INCLUDED

#include <fcppt/assert/pre.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	typename T,
	typename Enable = void
>
struct make_upper_bound;

template<
	typename T
>
struct make_upper_bound<
	T,
	typename
	boost::enable_if<
		std::is_floating_point<
			typename T::value_type
		>
	>::type
>
{
	typedef
	typename
	fcppt::random::distribution::parameters::uniform_real<
		T
	>::sup
	result_type;

	static
	result_type const
	execute(
		T const _value
	)
	{
		return
			result_type(
				_value
			);
	}
};

template<
	typename T
>
struct make_upper_bound<
	T,
	typename
	boost::disable_if<
		std::is_floating_point<
			typename T::value_type
		>
	>::type
>
{
	typedef
	typename
	fcppt::random::distribution::parameters::uniform_int<
		T
	>::max
	result_type;

	static
	result_type const
	execute(
		T const _value
	)
	{
		FCPPT_ASSERT_PRE(
			_value
			>
			fcppt::strong_typedef_construct_cast<
				T
			>(
				0
			)
		);

		return
			result_type(
				_value
				-
				fcppt::strong_typedef_construct_cast<
					T
				>(
					1
				)
			);
	}
};

}
}
}

#endif
