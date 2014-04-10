#ifndef SANGUIS_SERVER_RANDOM_SPLIT_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_SPLIT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/distributor_impl.hpp>
#include <sanguis/server/random/map_with_index.hpp>
#include <sanguis/server/random/max.hpp>
#include <sanguis/server/random/min.hpp>
#include <sanguis/server/random/split_array.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/transform/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	std::size_t Size
>
sanguis::server::random::split_array<
	Size
>
split(
	sanguis::random_generator &_random_generator,
	sanguis::server::random::min const _min,
	sanguis::server::random::max const _max,
	sanguis::server::random::split_array<
		Size
	> const &_sizes
)
{
	typedef
	sanguis::server::random::split_array<
		Size
	>
	result_type;

	typedef
	typename
	result_type::value_type
	value_type;

	typedef
	typename
	result_type::size_type
	size_type;

	typedef
	sanguis::server::random::distributor<
		value_type,
		size_type
	>
	distributor_type;

	distributor_type dist(
		sanguis::server::random::map_with_index(
			_sizes
		)
	);

	result_type result(
		fcppt::algorithm::array_init<
			result_type
		>(
			sanguis::server::random::amount(
				0u
			)
		)
	);

	typedef
	fcppt::random::distribution::parameters::uniform_int<
		sanguis::server::random::amount
	>
	size_parameters;

	sanguis::server::random::amount const draws(
		fcppt::random::distribution::make_basic(
			size_parameters(
				size_parameters::min(
					_min.get()
				),
				size_parameters::max(
					_max.get()
				)
			)
		)(
			_random_generator
		)
	);

	fcppt::algorithm::repeat(
		draws.get(),
		[
			&_random_generator,
			&dist,
			&result
		]()
		{
			++result[
				dist.execute(
					_random_generator
				)
			];
		}
	);

	return
		result;
}

}
}
}

#endif


