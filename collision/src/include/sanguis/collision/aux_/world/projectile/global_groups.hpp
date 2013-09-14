#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GLOBAL_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_GLOBAL_GROUPS_HPP_INCLUDED

#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/group_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace projectile
{

class global_groups
{
	FCPPT_NONCOPYABLE(
		global_groups
	);
public:
	explicit
	global_groups(
		sge::projectile::world &
	);

	~global_groups();

	sge::projectile::group::object &
	group(
		sanguis::collision::world::group
	) const;
private:
	typedef boost::ptr_map<
		sanguis::collision::world::group,
		sge::projectile::group::object
	> group_map;

	// TODO: why are the groups in projectile nonconst everywhere?
	mutable group_map groups_;
};

}
}
}
}
}

#endif
