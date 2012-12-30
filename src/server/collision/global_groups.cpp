#include <sanguis/exception.hpp>
#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <utility>
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

	init_map const init(
		fcppt::assign::make_container<
			init_map
		>
		(
			std::make_pair(
				sanguis::server::collision::group::enemy,
				sanguis::server::collision::group::projectile_player
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::pickup,
				sanguis::server::collision::group::player
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::player,
				sanguis::server::collision::group::projectile_enemy
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::sight_range,
				sanguis::server::collision::group::enemy
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::sight_range,
				sanguis::server::collision::group::player
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::sight_range,
				sanguis::server::collision::group::pickup
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::sight_range,
				sanguis::server::collision::group::projectile_enemy
			)
		)
		(
			std::make_pair(
				sanguis::server::collision::group::sight_range,
				sanguis::server::collision::group::projectile_player
			)
		)
	);

	for(
		init_map::const_iterator it(
			init.begin()
		);
		it != init.end();
		++it
	)
		_world.make_groups_collide(
			this->group(
				it->first
			),
			this->group(
				it->second
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

	if(
		it == groups_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Missing collision group in server!")
		);

	return *it->second;
}
