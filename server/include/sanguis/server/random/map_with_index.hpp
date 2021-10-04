#ifndef SANGUIS_SERVER_RANDOM_MAP_WITH_INDEX_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MAP_WITH_INDEX_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::random
{

template<
	typename Container
>
std::vector<
	std::pair<
		typename
		Container::value_type,
		typename
		Container::size_type
	>
>
map_with_index(
	Container const &_source
)
{
	std::vector<
		std::pair<
			typename
			Container::value_type,
			typename
			Container::size_type
		>
	>
	result{};

	result.reserve(
		_source.size()
	);

	for(
		typename
		Container::size_type index(
			0U
		);
		index < _source.size();
		++index
	)
	{
		result.push_back(
			std::make_pair(
				_source.get_unsafe(
					index
				),
				index
			)
		);
	}

	return
		result;
}

}

#endif
