#include <sanguis/collision/aux_/world/body_groups_for_body_group.hpp>
#include <sanguis/collision/aux_/world/ghost_groups_for_body_group.hpp>
#include <sanguis/collision/aux_/world/projectile/global_groups.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <memory>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

// TODO: Generalize find algorithms
template<
	typename Map
>
sge::projectile::group::object &
find_group(
	Map &_map,
	typename Map::key_type const _group
)
{
	auto const it(
		_map.find(
			_group
		)
	);

	FCPPT_ASSERT_ERROR(
		it != _map.end()
	);

	return
		*it->second;
}

template<
	typename Group
>
std::map<
	Group,
	std::unique_ptr<
		sge::projectile::group::object
	>
>
make_map(
	sge::projectile::world &_world
)
{
	return
		fcppt::algorithm::map<
			std::map<
				Group,
				std::unique_ptr<
					sge::projectile::group::object
				>
			>
		>(
			fcppt::make_enum_range<
				Group
			>(),
			[
				&_world
			](
				Group const _group
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
		);
}

}

sanguis::collision::aux_::world::projectile::global_groups::global_groups(
	sge::projectile::world &_world
)
:
	body_groups_(
		make_map<
			sanguis::collision::world::body_group
		>(
			_world
		)
	),
	ghost_groups_(
		make_map<
			sanguis::collision::world::ghost_group
		>(
			_world
		)
	)
{
	for(
		auto const cur_body_group
		:
		fcppt::make_enum_range<
			sanguis::collision::world::body_group
		>()
	)
	{
		for(
			auto const body_group_other
			:
			sanguis::collision::aux_::world::body_groups_for_body_group(
				cur_body_group
			)
		)
			_world.make_groups_collide(
				this->body_group(
					cur_body_group
				),
				this->body_group(
					body_group_other
				)
			);

		for(
			auto const cur_ghost_group
			:
			sanguis::collision::aux_::world::ghost_groups_for_body_group(
				cur_body_group
			)
		)
			_world.make_groups_collide(
				this->body_group(
					cur_body_group
				),
				this->ghost_group(
					cur_ghost_group
				)
			);
	}
}

sanguis::collision::aux_::world::projectile::global_groups::~global_groups()
{
}

sge::projectile::group::object &
sanguis::collision::aux_::world::projectile::global_groups::body_group(
	sanguis::collision::world::body_group const _group
) const
{
	return
		find_group(
			body_groups_,
			_group
		);
}

sge::projectile::group::object &
sanguis::collision::aux_::world::projectile::global_groups::ghost_group(
	sanguis::collision::world::ghost_group const _group
) const
{
	return
		find_group(
			ghost_groups_,
			_group
		);
}
