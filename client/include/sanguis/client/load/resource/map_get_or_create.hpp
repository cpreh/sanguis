#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_MAP_GET_OR_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_MAP_GET_OR_CREATE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

template<
	typename Key,
	typename Mapped,
	typename Comp,
	typename Alloc,
	typename Fun
>
Mapped &
map_get_or_create(
	std::map<Key, Mapped, Comp, Alloc> &_map,
	Key const &_key,
	Fun const &_creator
)
{
	typedef typename
	std::map<
		Key,
		Mapped,
		Comp,
		Alloc
	>::iterator
	iterator;

	iterator const it(
		_map.find(
			_key
		)
	);

	return
		it != _map.end()
		?
			it->second
		:
			_map.insert(
				std::make_pair(
					_key,
					_creator(
						_key
					)
				)
			).first->second
		;
}

}
}
}
}

#endif
