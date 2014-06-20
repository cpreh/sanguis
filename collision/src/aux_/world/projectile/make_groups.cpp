#include <sanguis/collision/aux_/world/projectile/global_groups.hpp>
#include <sanguis/collision/aux_/world/projectile/make_groups.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/make_ref.hpp>


sge::projectile::group::sequence
sanguis::collision::aux_::world::projectile::make_groups(
	sanguis::collision::world::group const _group,
	sanguis::collision::aux_::world::projectile::global_groups const &_global_groups
)
{
	return
		sge::projectile::group::sequence{
			fcppt::make_ref(
				_global_groups.group(
					_group
				)
			)
		};
}
