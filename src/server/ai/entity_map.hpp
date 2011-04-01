#ifndef SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED

#include "../entities/with_health_fwd.hpp"
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
		sanguis::entity_id,
		entities::with_health *
	>
> entity_map;

}
}
}

#endif
