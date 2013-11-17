#ifndef SANGUIS_SERVER_DRAW_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_DRAW_RANDOM_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

template<
	typename Result,
	typename Source,
	typename CreateFunction,
	typename LessFunction,
	typename EqualFunction
>
Result
draw_random(
	sanguis::random_generator &_random_generator,
	Source const &_source,
	typename Source::size_type const _limit,
	CreateFunction const &_create_function,
	LessFunction const &_less_function,
	EqualFunction const &_equal_function
)
{
	auto container_distribution(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices(
				_source
			)
		)
	);

	typedef
	typename
	Source::size_type
	size_type;

	typedef
	fcppt::random::distribution::parameters::uniform_int<
		size_type
	>
	size_parameter;

	size_type const draws(
		fcppt::random::distribution::make_basic(
			size_parameter(
				typename
				size_parameter::min(
					1u
				),
				typename
				size_parameter::max(
					_limit
				)
			)
		)(
			_random_generator
		)
	);

	Result result;

	result.reserve(
		draws
	);

	for(
		size_type index(
			0u
		);
		index < draws;
		++index
	)
		result.push_back(
			_create_function(
				_source[
					container_distribution(
						_random_generator
					)
				]
			)
		);

	std::sort(
		result.begin(),
		result.end(),
		_less_function
	);

	result.erase(
		std::unique(
			result.begin(),
			result.end(),
			_equal_function
		),
		result.end()
	);

	return
		std::move(
			result
		);
}

}
}

#endif
