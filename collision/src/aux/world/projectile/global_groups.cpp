#include <sanguis/collision/aux/world/group_relation.hpp>
#include <sanguis/collision/aux/world/projectile/global_groups.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sanguis::collision::aux::world::projectile::global_groups::global_groups(
	sge::projectile::world &_world
)
:
	groups_()
{
	FCPPT_FOREACH_ENUMERATOR(
		index,
		sanguis::collision::world::group
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

	for(
		auto pair
		:
		sanguis::collision::aux::world::group_relation()
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

sanguis::collision::aux::world::projectile::global_groups::~global_groups()
{
}

sge::projectile::group::object &
sanguis::collision::aux::world::projectile::global_groups::group(
	sanguis::collision::world::group const _group
) const
{
	auto const it(
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
