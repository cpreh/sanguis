#ifndef SANGUIS_LOAD_RESOURCE_MAP_GET_OR_CREATE_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_MAP_GET_OR_CREATE_HPP_INCLUDED

#include <map>
#include <utility>

namespace sanguis
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
	typename Fun>
Mapped& map_get_or_create(
	std::map<Key, Mapped, Comp, Alloc>& map, 
	Key const& key, 
	Fun const& creator)
{
	typename std::map<Key, Mapped, Comp, Alloc>::iterator it = map.find(key);
	return it != map.end() 
		? it->second 
		: map.insert(std::make_pair(key, creator(key))).first->second;
}
}
}
}

#endif
