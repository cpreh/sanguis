#ifndef SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED

#include "../entities/auto_weak_link_fwd.hpp"
#include "../../entity_id.hpp"
#include <fcppt/container/map_fwd.hpp>
#include <map>

namespace sanguis
{
namespace server
{
namespace ai
{

typedef fcppt::container::map<
	std::map<
		entity_id,
		entities::auto_weak_link // TODO: is a normal reference sufficient?
	>
> entity_map;

}
}
}

#endif
