#include "global_groups.hpp"
#include "group.hpp"
#include "../../exception.hpp"
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <vector>
#include <utility>

sanguis::server::collision::global_groups::global_groups(
	sge::projectile::world &_world
)
:
	groups_()
{
	FCPPT_FOREACH_ENUMERATOR(
		index,
		collision::group
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			groups_,
			index,
			fcppt::make_unique_ptr<
				sge::projectile::group::object
			>(
				fcppt::ref(
					_world
				)
			)
		);

	typedef std::vector<
		std::pair<
			group::type,
			group::type
		>
	> init_map;

	init_map const init(
		fcppt::assign::make_container<
			init_map
		>
		(
			std::make_pair(
				collision::group::enemy,
				collision::group::projectile_player
			)
		)
		(
			std::make_pair(
				collision::group::pickup,
				collision::group::player
			)
		)
		(
			std::make_pair(
				collision::group::player,
				collision::group::projectile_enemy
			)
		)
		(
			std::make_pair(
				collision::group::sight_range,
				collision::group::enemy
			)
		)
		(
			std::make_pair(
				collision::group::sight_range,
				collision::group::player
			)
		)
		(
			std::make_pair(
				collision::group::sight_range,
				collision::group::pickup
			)
		)
		(
			std::make_pair(
				collision::group::sight_range,
				collision::group::projectile_enemy
			)
		)
		(
			std::make_pair(
				collision::group::sight_range,
				collision::group::projectile_player
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
	collision::group::type const _group
) const
{
	collision::group_map::iterator const it(
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
