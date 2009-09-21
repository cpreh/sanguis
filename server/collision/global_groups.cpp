#include "global_groups.hpp"
#include <sge/collision/world.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/foreach_enumerator.hpp>

sanguis::server::collision::global_groups::global_groups(
	sge::collision::world_ptr const world_
)
:
	groups_()
{
	SGE_FOREACH_ENUMERATOR(
		index,
		group
	)
		groups_.insert(
			index,
			world_->create_group()
		);
}
