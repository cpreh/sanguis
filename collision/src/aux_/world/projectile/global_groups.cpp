#include <sanguis/collision/aux_/world/group_relation.hpp>
#include <sanguis/collision/aux_/world/projectile/global_groups.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux_::world::projectile::global_groups::global_groups(
	sge::projectile::world &_world
)
:
	groups_(
		fcppt::algorithm::map<
			group_map
		>(
			fcppt::make_enum_range<
				sanguis::collision::world::group
			>(),
			[
				&_world
			](
				sanguis::collision::world::group const _group
			)
			{
				return
					std::make_pair(
						_group,
						fcppt::make_unique_ptr<
							sge::projectile::group::object
						>(
							_world
						)
					);
			}
		)
	)
{
	for(
		auto pair
		:
		sanguis::collision::aux_::world::group_relation()
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

sanguis::collision::aux_::world::projectile::global_groups::~global_groups()
{
}

sge::projectile::group::object &
sanguis::collision::aux_::world::projectile::global_groups::group(
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
