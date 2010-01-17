#include "assign_groups.hpp"
#include "global_groups.hpp"
#include <boost/foreach.hpp>

sge::collision::shapes::container const
sanguis::server::collision::assign_groups(
	sge::collision::shapes::container const &shapes_,
	group_vector const &groups_,
	global_groups const &global_groups_
)
{
	BOOST_FOREACH(
		sge::collision::shapes::container::const_reference shape_,
		shapes_
	)
		BOOST_FOREACH(
			group_vector::const_reference group_,
			groups_
		)

			global_groups_.add_to_group(
				shape_,
				group_
			);
	
	return shapes_;
}
