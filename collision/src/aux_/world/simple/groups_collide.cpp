#include <sanguis/collision/aux_/world/group_pair.hpp>
#include <sanguis/collision/aux_/world/group_relation.hpp>
#include <sanguis/collision/aux_/world/simple/groups_collide.hpp>
#include <sanguis/collision/world/group.hpp>
#include <fcppt/homogenous_pair_comparison.hpp>
#include <fcppt/algorithm/contains_if.hpp>


bool
sanguis::collision::aux_::world::simple::groups_collide(
	sanguis::collision::world::group const _group1,
	sanguis::collision::world::group const _group2
)
{
	return
		fcppt::algorithm::contains_if(
			sanguis::collision::aux_::world::group_relation(),
			[
				_group1,
				_group2
			](
				sanguis::collision::aux_::world::group_pair const _pair
			)
			{
				return
					_pair
					==
					sanguis::collision::aux_::world::group_pair(
						_group1,
						_group2
					)
					||
					_pair
					==
					sanguis::collision::aux_::world::group_pair(
						_group2,
						_group1
					);
			}
		);
}
