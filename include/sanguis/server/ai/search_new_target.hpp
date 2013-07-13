#ifndef SANGUIS_SERVER_AI_SEARCH_NEW_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SEARCH_NEW_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::entities::auto_weak_link const
search_new_target(
	sanguis::server::entities::base const &owner,
	sanguis::server::ai::entity_set const &
);

}
}
}

#endif
