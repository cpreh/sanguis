#include "global_groups.hpp"
#include "group.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/group.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/foreach_enumerator.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <utility>

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
	
	typedef std::vector<
		std::pair<
			group::type,
			group::type
		>
	> init_map;

	init_map const init_(
		sge::assign::make_container<
			init_map
		>(
			std::make_pair(
				group::aggro_aura,
				group::player
			)
		)
		(
			std::make_pair(
				group::enemy,
				group::player
			)
		)
		(
			std::make_pair(
				group::sight_range,
				group::enemy
			)
		)
		(
			std::make_pair(
				group::sight_range,
				group::player
			)
		)
	);

	BOOST_FOREACH(
		init_map::const_reference ref,
		init_
	)
		world_->collides_with(
			groups_[
				ref.first
			],
			groups_[
				ref.second
			]
		);
}

void
sanguis::server::collision::global_groups::add_to_group(
	sge::collision::body_ptr const body_,
	group::type const group_
) const
{
	groups_[
		group_
	]->add(
		body_
	);
}

