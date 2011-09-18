#ifndef SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ENTITY_MAP_HPP_INCLUDED

#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/entity_id.hpp>
#include <fcppt/container/map_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

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
