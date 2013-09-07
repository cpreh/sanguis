#include <sanguis/collision/aux/world/projectile/global_groups.hpp>
#include <sanguis/collision/aux/world/projectile/make_groups.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/make_ref.hpp>


sge::projectile::group::sequence const
sanguis::collision::aux::world::projectile::make_groups(
	sanguis::collision::world::group_vector const &_groups,
	sanguis::collision::aux::world::projectile::global_groups const &_global_groups
)
{
	sge::projectile::group::sequence ret;

	for(
		auto const &group : _groups
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
