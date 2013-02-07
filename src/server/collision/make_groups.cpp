#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/collision/make_groups.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/make_ref.hpp>


sge::projectile::group::sequence const
sanguis::server::collision::make_groups(
	sanguis::server::collision::group_vector const &_groups,
	sanguis::server::collision::global_groups const &_global_groups
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
