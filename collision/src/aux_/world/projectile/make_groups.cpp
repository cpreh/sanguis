#include <sanguis/collision/aux_/world/projectile/global_groups.hpp>
#include <sanguis/collision/aux_/world/projectile/make_groups.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_ref.hpp>


sge::projectile::group::sequence const
sanguis::collision::aux_::world::projectile::make_groups(
	sanguis::collision::world::group_field const &_groups,
	sanguis::collision::aux_::world::projectile::global_groups const &_global_groups
)
{
	sge::projectile::group::sequence ret;

	FCPPT_FOREACH_ENUMERATOR(
		group,
		sanguis::collision::world::group
	)
		if(
			_groups[
				group
			]
		)
			ret.push_back(
				fcppt::make_ref(
					_global_groups.group(
						group
					)
				)
			);

	return ret;
}
