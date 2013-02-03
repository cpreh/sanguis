#ifndef SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED

#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/collision/group_fwd.hpp>
#include <sanguis/server/collision/group_map.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace collision
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
		sanguis::server::collision::group
	) const;
private:
	// TODO: why are the groups in projectile nonconst everywhere?
	mutable sanguis::server::collision::group_map groups_;
};

}
}
}

#endif
