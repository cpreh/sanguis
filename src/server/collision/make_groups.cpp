#include "make_groups.hpp"
#include "global_groups.hpp"
#include <fcppt/ref.hpp>

sge::projectile::group::sequence const
sanguis::server::collision::make_groups(
	collision::group_vector const &_groups,
	collision::global_groups const &_global_groups
)
{
	sge::projectile::group::sequence ret;

	for(
		collision::group_vector::const_iterator it(
			_groups.begin()
		);
		it != _groups.end();
		++it
	)
		ret.push_back(
			fcppt::ref(
				_global_groups->group(
					*it
				)
			)
		);
	
	return ret;
}
