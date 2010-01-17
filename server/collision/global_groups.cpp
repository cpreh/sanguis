#include "global_groups.hpp"
#include "group.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/group.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <utility>

sanguis::server::collision::global_groups::global_groups(
	sge::collision::world_ptr const world_
)
:
	groups_()
{
	FCPPT_FOREACH_ENUMERATOR(
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
		fcppt::assign::make_container<
			init_map
		>
		(
			std::make_pair(
				group::enemy,
				group::projectile_player
			)
		)
		(
			std::make_pair(
				group::pickup,
				group::player
			)
		)
		(
			std::make_pair(
				group::player,
				group::projectile_enemy
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
		(
			std::make_pair(
				group::sight_range,
				group::pickup
			)
		)
		(
			std::make_pair(
				group::sight_range,
				group::projectile_enemy
			)
		)
		(
			std::make_pair(
				group::sight_range,
				group::projectile_player
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
	sge::collision::shapes::base_ptr const shape_,
	group::type const group_
) const
{
	groups_[
		group_
	]->add(
		shape_
	);
}

