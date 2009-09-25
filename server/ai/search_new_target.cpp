#include "search_new_target.hpp"
#include "../entities/auto_weak_link.hpp"
#include <sge/container/map_impl.hpp>

sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	entities::base const &owner_,
	entity_map const &entities_
)
{
	// FIXME:
	return entities_.begin()->second;
}
