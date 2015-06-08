#ifndef SANGUIS_SERVER_RANDOM_DRAW_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_DRAW_HPP_INCLUDED

#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/create_function.hpp>
#include <sanguis/server/random/equal_function.hpp>
#include <sanguis/server/random/less_function.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/random/wrapper/make_uniform_container.hpp>
#include <fcppt/random/wrapper/uniform_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	typename Result,
	typename Source
>
Result
draw(
	sanguis::random_generator &_random_generator,
	Source const &_source,
	sanguis::server::random::amount const _draws,
	sanguis::server::random::create_function<
		typename
		Result::value_type,
		typename
		Source::value_type
	> const &_create_function,
	sanguis::server::random::less_function<
		typename
		Result::value_type
	> const &_less_function,
	sanguis::server::random::equal_function<
		typename
		Result::value_type
	> const &_equal_function
)
{
	return
		fcppt::maybe(
			fcppt::random::wrapper::make_uniform_container(
				_source
			),
			[]{
				return
					Result();
			},
			[
				&_random_generator,
				&_less_function,
				&_create_function,
				&_equal_function,
				&_source,
				&_draws
			](
				fcppt::random::wrapper::uniform_container<
					Source const
				> _container_distribution
			)
			{
				Result result;

				result.reserve(
					std::min(
						fcppt::cast::size<
							typename
							Source::size_type
						>(
							_draws.get()
						),
						_source.size()
					)
				);

				fcppt::algorithm::repeat(
					result.capacity(),
					[
						&_create_function,
						&_random_generator,
						&_container_distribution,
						&result
					]()
					{
						result.push_back(
							_create_function.get()(
								_container_distribution(
									_random_generator
								)
							)
						);
					}
				);

				std::sort(
					result.begin(),
					result.end(),
					_less_function.get()
				);

				result.erase(
					std::unique(
						result.begin(),
						result.end(),
						_equal_function.get()
					),
					result.end()
				);

				return
					result;
			}
		);
}

}
}
}

#endif
