#ifndef SANGUIS_SERVER_AI_SEARCH_NEW_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SEARCH_NEW_TARGET_HPP_INCLUDED

#include "entity_map.hpp"
#include "../entities/auto_weak_link_fwd.hpp"
#include "../entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace ai
{

entities::auto_weak_link const
search_new_target(
	entities::entity const &owner,
	entity_map const &
);

}
}
}

#endif
