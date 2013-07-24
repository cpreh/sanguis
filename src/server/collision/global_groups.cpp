#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::global_groups::global_groups(
	sge::projectile::world &_world
)
:
	groups_()
{
	FCPPT_FOREACH_ENUMERATOR(
		index,
		sanguis::server::collision::group
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			groups_,
			index,
			fcppt::make_unique_ptr<
				sge::projectile::group::object
			>(
				_world
			)
		);

	typedef std::vector<
		std::pair<
			sanguis::server::collision::group,
			sanguis::server::collision::group
		>
	> init_map;

	init_map const init{
		std::make_pair(
			sanguis::server::collision::group::enemy,
			sanguis::server::collision::group::projectile_player
		),
		std::make_pair(
			sanguis::server::collision::group::pickup,
			sanguis::server::collision::group::player
		),
		std::make_pair(
			sanguis::server::collision::group::player,
			sanguis::server::collision::group::projectile_enemy
		),
		std::make_pair(
			sanguis::server::collision::group::sight_range,
			sanguis::server::collision::group::enemy
		),
		std::make_pair(
			sanguis::server::collision::group::sight_range,
			sanguis::server::collision::group::player
		),
		std::make_pair(
			sanguis::server::collision::group::sight_range,
			sanguis::server::collision::group::pickup
		),
		std::make_pair(
			sanguis::server::collision::group::sight_range,
			sanguis::server::collision::group::projectile_enemy
		),
		std::make_pair(
			sanguis::server::collision::group::sight_range,
			sanguis::server::collision::group::projectile_player
		),
		std::make_pair(
			sanguis::server::collision::group::obstacle,
			sanguis::server::collision::group::projectile_player
		),
		std::make_pair(
			sanguis::server::collision::group::obstacle,
			sanguis::server::collision::group::player
		),
		std::make_pair(
			sanguis::server::collision::group::obstacle,
			sanguis::server::collision::group::projectile_enemy
		),
		std::make_pair(
			sanguis::server::collision::group::obstacle,
			sanguis::server::collision::group::enemy
		)
	};

	for(
		auto pair : init
	)
		_world.make_groups_collide(
			this->group(
				pair.first
			),
			this->group(
				pair.second
			)
		);
}

sanguis::server::collision::global_groups::~global_groups()
{
}

sge::projectile::group::object &
sanguis::server::collision::global_groups::group(
	sanguis::server::collision::group const _group
) const
{
	sanguis::server::collision::group_map::iterator const it(
		groups_.find(
			_group
		)
	);

	FCPPT_ASSERT_ERROR(
		it != groups_.end()
	);

	return
		*it->second;
}
