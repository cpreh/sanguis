#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED

#include "sight_range_entry.hpp"
#include "../../entity_id.hpp"
#include <functional>
#include <set>

namespace sanguis
{
namespace server
{
namespace world
{

typedef std::set<
	sight_range_entry,
	std::pointer_to_binary_function<
		sight_range_entry const &,
		sight_range_entry const &,
		bool
	>
> sight_range_entry_set;

}
}
}

#endif
