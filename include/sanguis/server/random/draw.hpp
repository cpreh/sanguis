#ifndef SANGUIS_SERVER_RANDOM_DRAW_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_DRAW_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/amount.hpp>
#include <fcppt/algorithm/repeat.hpp>
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
namespace random
{

template<
	typename Result,
	typename Source,
	typename CreateFunction,
	typename LessFunction,
	typename EqualFunction
>
Result
draw(
	sanguis::random_generator &_random_generator,
	Source const &_source,
	sanguis::server::random::amount const _draws,
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

	Result result;

	result.reserve(
		_draws.get()
	);

	fcppt::algorithm::repeat(
		_draws.get(),
		[
			&_create_function,
			&_source,
			&_random_generator,
			&container_distribution,
			&result
		]()
		{
			result.push_back(
				_create_function(
					_source[
						container_distribution(
							_random_generator
						)
					]
				)
			);
		}
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
}

#endif
