#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

typedef std::unordered_set<
	sanguis::entity_id
> sight_range_entry_set;

}
}
}

#endif
